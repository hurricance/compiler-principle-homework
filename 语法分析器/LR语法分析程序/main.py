#预测分析表函数， x为当前状态， y为输入的字符串， 通过这两个参数映射到对应的执行过程
def mapping(x, y):
    if x == '0':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'E':
            return '1'
        elif y == 'T':
            return '2'
        elif y == 'F':
            return '3'
    elif x == '1':
        if y == '+':
            return 'S6'
        elif y == '-':
            return 'S7'
        elif y == '$':
            return 'ACC'
    elif x == '2':
        if y == '*':
            return 'S8'
        elif y == '/':
            return 'S9'
        elif y == '$' or y == '+' or y == '-' or y == ')':
            return 'R3'
    elif x == '3':
        if y == '$' or y == '+' or y == '-' or y == ')' or y == '*' or y == '/':
            return 'R6'
    elif x == '4':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'E':
            return '10'
        elif y == 'T':
            return '2'
        elif y == 'F':
            return '3'
    elif x == '5':
        if y == '$' or y == '+' or y == '-' or y == '*' or y == '/' or y == ')':
            return 'R8'
    elif x == '6':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'T':
            return '11'
        elif y == 'F':
            return '3'
    elif x == '7':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'T':
            return '12'
        elif y == 'F':
            return '3'
    elif x == '8':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'F':
            return '13'
    elif x == '9':
        if y == '(':
            return 'S4'
        elif y == 'n':
            return 'S5'
        elif y == 'F':
            return '14'
    elif x == '10':
        if y == '+':
            return 'S6'
        elif y == '-':
            return 'S7'
        elif y == ')':
            return 'S15'
    elif x == '11':
        if y == '*':
            return 'S8'
        elif y == '/':
            return 'S9'
        elif y == '$' or y == '+' or y == '-' or y == ')':
            return 'R1'
    elif x == '12':
        if y == '*':
            return 'S8'
        elif y == '/':
            return 'S9'
        elif y == '$' or y == '+' or y == '-' or y == ')':
            return 'R2'
    elif x == '13':
        if y == '$' or y == '+' or y == '-' or y == ')' or y == '*' or y == '/':
            return 'R4'
    elif x == '14':
        if y == '$' or y == '+' or y == '-' or y == ')' or y == '*' or y == '/':
            return 'R5'
    elif x == '15':
        if y == '$' or y == '+' or y == '-' or y == ')' or y == '*' or y == '/':
            return 'R7'

#在规约过程中， 需要删减栈中的内容， 此函数用于确定规约过程中需要出栈的字符的个数
def count(i):
    if i == '1' or i == '2' or i == '4' or i == '5' or i == '7':
        return int(3)
    else:
        return int(1)

#用于求出规约过程中得到的非终结符
def get_char(i):
    if i == '1' or i == '2' or i == '3':
        return 'E'
    elif i == '4' or i == '5' or i == '6':
        return 'T'
    elif i == '7' or i == '8':
        return 'F'

#主函数入口
if __name__ == "__main__":
    while True:
        print('please enter string you want to analyze:')
        stack = [{'0': '_'}] #stack用于存储当前状态以及栈中字符
        s = input()
        s = s + '$'
        i = 0
        sp = 0
        print("栈                   输入                    输出")
        #以下为算法4.3内容
        while True:
            for j in range(sp + 1):
                print(f"{list(stack[j])[0]}/{list(stack[j].values())[0]}", end = ' ')
            print("                 ", end = '')
            for j in range(i, len(s)):
                print(s[j], end = '')
            #用于捕获异常， 当mapping未映射到值时， 抛出异常
            try:
                if mapping(list(stack[sp])[0], s[i])[0] == 'S':
                    pass
            except TypeError:
                print('\nfail to match!')
                break
            if mapping(list(stack[sp])[0], s[i])[0] == 'S':
                temp = mapping(list(stack[sp])[0], s[i])[1:]
                stack.append({temp : s[i]})
                i += 1
                sp += 1
                print(f"                        shift {int(temp)}")
            elif mapping(list(stack[sp])[0], s[i])[0] == 'R':
                temp = count(mapping(list(stack[sp])[0], s[i])[1:])
                c = get_char(mapping(list(stack[sp])[0], s[i])[1:])
                sp -= temp
                tp = ''
                pf = stack[sp + 1:sp + temp + 1]
                for item in pf:
                    tp += list(item.values())[0]
                stack = stack[0:sp + 1]
                temp = mapping(list(stack[sp])[0], c)
                stack.append({temp : c})
                sp += 1
                print(f"                    reduced by {c} -> {tp}")
            elif mapping(list(stack[sp])[0], s[i]) == 'ACC':
                print('                     ACC')
                print('successfully match')
                print('')
                break
            else:
                print('fail to match')
                print('')
                break

