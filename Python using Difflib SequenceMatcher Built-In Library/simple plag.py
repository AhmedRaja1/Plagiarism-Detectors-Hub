from difflib import SequenceMatcher


with open("1.txt", encoding="utf8") as file1, open ("2.txt", encoding="utf8") as file2:
    file1data = file1.read()
    file2data = file2.read()

plagiarism = SequenceMatcher(None, file1data, file2data).ratio()

print(plagiarism)
