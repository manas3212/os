def optimal_page_replace(page_sequence, capacity):
    pages = []
    page_faults = 0

    for current_page in page_sequence:
        if current_page not in pages:
            page_faults += 1

            if len(pages) < capacity:
                pages.append(current_page)
            else:
                pages_to_replace = [page for page in pages if page not in page_sequence]
                if pages_to_replace:
                    pages[pages.index(pages_to_replace[0])] = current_page

    return page_faults

if __name__ == "__main__":
    page_sequence = [1, 2, 3, 4, 1, 5, 2, 4, 1, 3, 2, 5]
    capacity = 3

    page_faults = optimal_page_replace(page_sequence, capacity)

    print("Total number of Page Faults:", page_faults)
