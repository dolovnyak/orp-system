from sys import argv


def error(message):
    print(message)
    exit(1)


def is_stock_string(string):
    return string.count(':') == 1 and not string.startswith('optimize:')

def is_process_string(string):
    return string.count(':') >= 4 and not is_stock_string(string)

def parse_stock_string(string):
    result = [x.strip() for x in string.split(':')]
    result[1] = int(result[1])
    return result

def create_process(name, sources, products, delay):
    sources = sources.split(';')
    splitted_sources = {}
    for source in sources:
        source = source.split(':')
        if len(source) != 2:
            error('parse source file error')
        source[1] = int(source[1])
        if source[0] in splitted_sources:
            splitted_sources[source[0]] += source[1]
        else:
            splitted_sources[source[0]] = source[1]

    products = products.split(';')
    splitted_products = {}
    for source in products:
        source = source.split(':')
        if len(source) != 2:
            error('parse source file error')
        source[1] = int(source[1])
        if source[0] in splitted_products:
            splitted_products[source[0]] += source[1]
        else:
            splitted_products[source[0]] = source[1]

    process = {
        'name': name,
        'sources': splitted_sources,
        'products': splitted_products,
        'delay': int(delay),
    }

    return process

def parse_process_string(string):
    substrings = string.split(':')
    is_bracked = False
    buffer = ''
    chanks = []

    for substring in substrings:
        if '(' in substring:
            if substring.count('(') > 1 or substring.count(')') > 0 or substring[0] != '(':
                error('parse source file error')
            if is_bracked:
                error('parse source file error')
            buffer = substring
            is_bracked = True
        elif ')' in substring:
            if substring.count(')') > 1 or substring.count('(') > 0 or substring[-1] != ')':
                error('parse source file error')
            if not is_bracked:
                error('parse source file error')
            buffer = f'{buffer}:{substring}'
            chanks.append(buffer)
            buffer = ''
            is_bracked = False
        else:
            if is_bracked:
                buffer = f'{buffer}:{substring}'
            else:
                chanks.append(substring)

    if len(chanks) != 4:
        error('parse source file error')

    sub = []
    sub.append(chanks[0])
    sub.append(chanks[1][1:-1])
    sub.append(chanks[2][1:-1])
    sub.append(chanks[3])

    return create_process(sub[0], sub[1], sub[2], sub[3])

def parse_file_data(path):
    try:
        file = open(path, 'r').read()
    except:
        error(f'file "{path}" reading error')
    strings = (x.split('#')[0] for x in file.split('\n') if x)
    strings = (x for x in strings if x)

    stock = []
    processes = []

    for string in strings:
        if is_stock_string(string):
            stock.append(string)
        elif is_process_string(string):
            processes.append(string)

    stock_parsed = {}
    processes_parsed = {}

    for string in stock:
        try:
            key, value = parse_stock_string(string)
            if key in stock_parsed:
                stock_parsed[key] += value
            else:
                stock_parsed[key] = value
        except Exception as e:
            pass

    for string in processes:
        try:
            process = parse_process_string(string)
            processes_parsed[process['name']] = process
            process.pop('name')
        except Exception as e:
            pass

    return stock_parsed, processes_parsed

def parse_result(path):
    try:
        file = open(path, 'r').read()
    except:
        error(f'file "{path}" reading error')

    is_1 = False
    is_2 = False

    operations = []
    result_stock = {}

    try:
        for string in file.split('\n'):
            if string == 'Main walk':
                is_1 = True
                continue
            elif string == 'Stock :':
                is_2 = True
                continue
            if is_1 and not is_2:
                if ':' in string:
                    x, y = tuple(string.split(':'))
                    x = int(x)
                    operations.append((y, x))
            elif is_2:
                if string:
                    x, y = tuple(string.split('=>'))
                    x = x.strip()
                    y = int(y.strip())
                    result_stock[x] = y
    except Exception as e:
        error('parse result file error')

    return operations, result_stock

def check(stock, processes, operations, result_stock):
    operations_dict = {}


    for name, delay in operations:
        if delay in operations_dict:
            pass
        else:
            operations_dict[delay] = {'minus': [], 'plus': []}
        if name not in processes:
            continue
            error('invalid process name')
        new_delay = delay + processes[name]['delay']
        if new_delay in operations_dict:
            pass
        else:
            operations_dict[new_delay] = {'minus': [], 'plus': []}

    for name, delay in operations:
        operations_dict[delay]['minus'].append(name)
        if name in processes:
            operations_dict[delay + processes[name]['delay']]['plus'].append(name)

    delays = sorted(operations_dict.keys())

    for delay in delays:

        to_do = operations_dict[delay]
        #print(f'BEFORE STOCK ({delay}):', stock)
        for plus in to_do['plus']:
            process = processes[plus]['products']
            for source, count in process.items():
                if source not in stock:
                    stock[source] = 0
                stock[source] += count
        for minus in to_do['minus']:
            process = processes[minus]['sources']
            for source, count in process.items():
                if source not in stock:
                    stock[source] = 0
                stock[source] -= count
                if stock[source] < 0:
                    error(f'impossible operation in {delay} cycle: "{minus}" ({delay}) (resource "{source}" went into negative)')
        #print('AFTER STOCK:', stock)

    #print(stock)
    #print(result_stock)
    for key, value in stock.items():
        if key not in result_stock or result_stock[key] != stock[key]:
            error(f'the totals do not converge ({key})')

    print("it's correct")


def main():
    if len(argv) != 3:
        error('usage: python3 krpsim_verif.py [file] [result_to_test]')
    try:
        stock, processes = parse_file_data(argv[1])
        operations, result_stock = parse_result(argv[2])
        #print(stock, processes, operations, result_stock)
        check(stock, processes, operations, result_stock)
    except:
        error('invalid file')


if __name__ == '__main__':
    main()
