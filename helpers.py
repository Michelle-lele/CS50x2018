from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # create sets for a & b
    lines_of_a = set(a.splitlines())
    lines_of_b = set(b.splitlines())
    matching_lines_a_b = lines_of_a.intersection(lines_of_b)

    return list(matching_lines_a_b)


def sentences(a, b):
    """Return sentences in both a and b"""
    sentences_of_a = set(sent_tokenize(a))
    sentences_of_b = set(sent_tokenize(b))
    matching_sentences_a_b = sentences_of_a.intersection(sentences_of_b)

    return list(matching_sentences_a_b)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_of_a = set()
    substrings_of_b = set()
    range_a = len(a) - n + 1
    range_b = len(b) - n + 1
    for i in range(range_a):
        substrings_of_a.add(a[(0 + i): (n + i)])

    for i in range(range_b):
        substrings_of_b.add(b[(0 + i): (n + i)])

    matching_substrings_a_b = substrings_of_a.intersection(substrings_of_b)

    return list(matching_substrings_a_b)