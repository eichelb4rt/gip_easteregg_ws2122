def main():
    input_text = "https://discord.gg/MyhP6T65e2"
    for char in input_text:
        line = "BRUH " * ord(char)
        line = line[:-1]
        print(line)

if __name__ == "__main__":
    main()