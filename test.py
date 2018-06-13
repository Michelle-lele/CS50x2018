from nltk.tokenize import sent_tokenize
# import pdb
# pdb.run('test.test()')

x = "foo"
y = "bar"

def lines(a, b):
    """Return lines in both a and b"""
    # create data structure for a
    lines_of_a = set(a.splitlines())
    lines_of_b = set(b.splitlines())
    matching_lines_a_b = lines_of_a.intersection(lines_of_b)


    return list(matching_lines_a_b)

# print(lines(x, y))

def sentences(a, b):
    """Return sentences in both a and b"""
    sentences_of_a = set(sent_tokenize(a))
    sentences_of_b = set(sent_tokenize(b))
    matching_sentences_a_b = sentences_of_a.intersection(sentences_of_b)

    return list(matching_sentences_a_b)

# print(sentences(x,y))

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_of_a = set()
    substrings_of_b = set()

    range_a = len(a) - n + 1
    print(range_a)
    range_b = len(b) - n + 1
    print(range_b)
    for i in range(range_a):
        substrings_of_a.add(a[(0 + i): (n + i)])
        print("substrings_of_a")
        print(substrings_of_a)
        print(i)

    for i in range(range_b):
        substrings_of_b.add(b[(0 + i): (n + i)])
        print("substrings_of_b")
        print(substrings_of_b)
        print(i)

    matching_substrings_a_b = substrings_of_a.intersection(substrings_of_b)

    return list(matching_substrings_a_b)

print(substrings(x, y, 1))