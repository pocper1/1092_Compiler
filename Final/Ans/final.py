debugging = False

def init_scope():

    def _add(*args):
        return sum(args)

    def _mul(*args):
        n = 1
        for i in args:
            n *= i
        return n
    
    def _equ(*args):
        for n in args[1:]:
            if args[0] != n:
                return False
        return True
    
    def _and(*args):
        return all(args)
    
    def _or(*args):
        return any(args)
    
    return {
        '+':            Function('+', _add,                         int, '>= 2'),
        '-':            Function('-', lambda x, y: x - y,           int, '== 2'),
        '*':            Function('*', _mul,                         int, '>= 2'),
        '/':            Function('/', lambda x, y: x // y,          int, '== 2'),
        'mod':          Function('mod', lambda x, y: x % y,         int, '== 2'),
        '=':            Function('=', _equ,                         'same', '>= 2'),
        '>':            Function('>', lambda x, y: x > y,           int, '== 2'),
        '<':            Function('<', lambda x, y: x < y,           int, '== 2'),
        'and':          Function('and', _and,                       bool, '>= 2'),
        'or':           Function('or', _or,                         bool, '>= 2'),
        'not':          Function('not', lambda x: not x,            bool, '== 1'),
        'print-num':    Function('print-num',   lambda x: print(x), int, '== 1'),
        'print-bool':   Function('print-bool', lambda x: print({True: '#t', False: '#f'}[x]), bool, '== 1')
    }

def debug(*args, indent=0, **kwargs):
    if debugging:
        indent = '    ' * indent
        print(f'\033[2m---> {indent}{" ".join(map(str, args))}\033[0m', **kwargs)

def success(*args, **kwargs):
    print(f'\033[92m{" ".join(map(str, args))}\033[0m', **kwargs)

def warning(*args, **kwargs):
    print(f'\033[93m{" ".join(map(str, args))}\033[0m', **kwargs)

def is_id(s):
    c, *r = s
    if not c.islower():
        return False
    for c in r:
        if not (c.islower() or c == '-'):
            return False
    return True

def parse_tree(code):
    tokens = code.replace('(', ' ( ').replace(')', ' ) ').split()
    tree_code = []
    for token in tokens:
        if token not in ['(', ')']:
            tree_code.append(f'"{token}"')
        else:
            tree_code.append(token)
        if token != '(':    
            tree_code.append(',')
    return eval(''.join(['(', *tree_code, ')']))

class Function:
    def __init__(self, name='annoymous', func=None, arg_type=None, n_args=''):
        self.name = name
        self.func = func
        self.arg_type = arg_type
        self.n_args = n_args
        self.locked = False

    def __call__(self, *args):
        self._check_args(args)
        return self.func(*args)
    
    def _check_args(self, args):
        n_args = len(args)
        assert eval(f'{n_args} {self.n_args}'), (
            f'expect number of arguments {self.n_args}, got {n_args}')
        if self.arg_type is not None:
            if self.arg_type == 'same':
                arg_type = type(args[0])
            else:
                arg_type = self.arg_type
            for i, arg in enumerate(args):
                if type(arg) != arg_type:
                    n = i + 1
                    t1 = getattr(arg_type, '__name__', arg_type).lower()
                    t2 = getattr(type(arg), '__name__', type(arg)).lower()
                    assert False, f'expect argument {n} with type {t1} but got {t2}'

    def __str__(self):
        info = ''
        if self.n_args is not None:
            n_args = self.n_args.replace('== ', '')
            info += ' ({} args)'.format(n_args)
        if self.arg_type is not None:
            arg_type = getattr(self.arg_type, '__name__', str(self.arg_type))
            info += ' (type {})'.format(arg_type)
        return f"<function '{self.name}'{info}>"
    
    def __repr__(self):
        return str(self)


def evaluate(statement, scope, layer=0):
    if isinstance(statement, tuple):

        assert len(statement), 'missing function'
        primary = statement[0]
        
        if primary == 'define':
            _, name, value = statement
            assert is_id(name), f'invalid id: {name}'
            if type(value) is tuple:
                temp_scope = scope.copy()
                temp_scope[name] = Function(name)
                temp_scope[name].locked = True
                temp = evaluate(value, temp_scope, layer + 1)
                if callable(temp) and temp != temp_scope[name]:
                    temp_scope[name].locked = False
                    temp_scope[name].func = temp.func
                    temp_scope[name].n_args = temp.n_args
                    scope[name] = temp_scope[name]
                    return
            scope[name] = evaluate(value, scope, layer + 1)
            return

        if primary == 'fun':
            _, arg_names, *defines, exp = statement
            n_args = len(arg_names)
            static_scope = scope.copy()
            for define in defines:
                evaluate(define, static_scope, layer + 1)
            def _func(*args):
                func_scope = static_scope.copy()
                for arg_name, arg in zip(arg_names, args):
                    func_scope[arg_name] = evaluate(arg, scope, layer + 1)
                return evaluate(exp, func_scope, layer + 1)
            return Function(func=_func, n_args=f'== {n_args}')

        if primary == 'if':
            _, cond, true, false = statement
            if evaluate(cond, scope, layer + 1):
                return evaluate(true, scope, layer + 1)
            else:
                return evaluate(false, scope, layer + 1)
        if isinstance(primary, tuple):
            primary = evaluate(primary, scope, layer + 1)
            assert type(primary) == Function, (
                f'expect a function but got {type(primary).__name__}')
            statement = (primary, *statement[1:])
            return evaluate(statement, scope, layer)

        func = None

        if isinstance(primary, Function):
            func, *args = statement
        
        elif type(primary) is str and primary in scope:
            func_name, *args = statement
            func = scope[func_name]
        
        if func is not None:
            assert callable(func), f'{func} is not callable'
            args = [evaluate(arg, scope, layer + 1) for arg in args]
            debug('| call:', func.name, args, indent=layer)
            assert not func.locked, f'calling an incomplete function: {func.name}'
            value = func(*args)
            debug('| return:', value, indent=layer)
            return value
        
        assert not is_id(primary), f'undefined function: {primary}'
        assert False, f'invalid function name: {primary}'

    else:
        if callable(statement):
            return statement

        try:
            return int(statement)
        except:
            pass
        
        try:
            return {'#t': True, '#f': False}[statement]
        except:
            pass
            
        try:
            return scope[statement]
        except:
            pass
        
        assert not is_id(statement), f'undefined variable: {statement}'
        assert False, f'invalid syntax: {statement}'

def run(code, scope=init_scope(), interactive=False):
    statements = parse_tree(code)
    for statement in statements:
        try:
            retval = evaluate(statement, scope)
            if (debugging or interactive) and retval is not None:
                success('===>', retval)
        except Exception as e:
            if debugging:
                import traceback
                warning(traceback.format_exc())
            elif interactive:
                warning('Error:', str(e) or 'invalid syntax')
            else:
                print('Error:', str(e) or 'invalid syntax')

if __name__ == '__main__':
    import sys, os, readline

    if len(sys.argv) > 1 and os.path.isfile(sys.argv[1]):
        run(open(sys.argv[1]).read())
    else:
        while True:
            try:
                run(input('final> '), interactive=True)
            except:
                break