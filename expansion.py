    


class Expansion(object):
    def __init__(self, begin, end, func, argstr):
        self.begin = begin
        self.end = end
        self.func = func
        self.argstr = argstr

    def apply(self, seq):
        before = seq[:begin]
        after = seq[end:]
        return before + self.func(self.argstr) + end


class Expansion(object):
    def __init__(self, seq, values, functions):
        self.seq = seq
        self.values = values
        self.functions = functions

    def expand(self):
        result = self._expand_values()
        return result

    def _expand_values(self):
        result = self.seq
        for var, value in self.values.items():
            var = '$(%s)' % var
            result = result.replace(var, value)
        return result

    def _expand_functions(self, seq):
        funcname = ''
        state = 'init'
        nesting = []
        for i, c in enumerate(seq):
            if state == 'init':
                if c == '$':
                    state = 'dollar'

            if state == 'dollar':
                if c == '(':
                    state = 'name'
                    nesting.append(i)

            if state == 'name':
                if c == '$' or c == ')':
                    raise SyntaxError('Invalid syntax')
                elif c == ' ':
                    state = 'arg'
                else:
                    funcname += c

            if state == 'arg':
                if c == '$':
                    raise SyntaxError('Invalid syntax')
                elif c == ' ':
                    state = 'arg'
                elif c != ')':
                    funcname += c
