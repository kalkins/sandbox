def read_pipe():
    with open('/tmp/sandbox_pipe', 'w') as pipe:
        pipe.write('r')
        pipe.flush()

    with open('/tmp/sandbox_pipe', 'r') as pipe:
        size = int(pipe.readline())
        vec = [int(pipe.readline()) for _ in range(size)]

    return vec


def main():
    for _ in range(2):
        vec = read_pipe()
        print(f'Received {vec}')


if __name__ == '__main__':
    main()
