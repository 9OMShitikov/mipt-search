#!/usr/bin/python3

import csv
import os
from tqdm.auto import tqdm


def abs_path(relative_path):
    __current_path = os.path.dirname(os.path.abspath(__file__))
    return os.path.join(__current_path, relative_path)


template_index = {
    'stopwords': abs_path('etc/stopwords.txt'),
    'wordforms': abs_path('etc/wordforms.txt')
}


def print_index(index_name, index_base, index_type, params, fw):
    if index_base == '':
        print('index {}'.format(index_name), file=fw)
    else:
        print('index {} : {}'.format(index_name, index_base), file=fw)
    print('{', file=fw)
    print('\ttype = {}'.format(index_type), file=fw)

    for key in params:
        print('\t{} = {}'.format(key, params[key]), file=fw)

    print('}', file=fw)


categories = set([])
with open('data/category.csv') as csvfile:
    csvfile.readline()  # skip header
    categories_reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    for row in categories_reader:
        if len(row) != 2:
            continue
        category_id, _ = row
        categories.add(int(category_id))

fw_categories = dict([])
csv_categories = dict([])
for category_id in categories:
    fw_categories[category_id] = open("data/category_{}.csv".format(category_id), 'w')
    csv_categories[category_id] = csv.writer(fw_categories[category_id], delimiter=',', quotechar='"')

with open('data/train.csv', 'r') as csvfile:
    header = csvfile.readline()  # skip header
    for category_id in categories:
        print(header, file=fw_categories[category_id], end="")

    data_reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    for row in tqdm(data_reader):
        item_id, title, description, price, category_id = row
        csv_categories[int(category_id)].writerow(row)

for category_id in categories:
    fw_categories[category_id].close()

conf_path = abs_path('etc/mipt_search.conf')

with open(conf_path, 'w') as fw:
    print_index('template', '', 'template', template_index, fw)
    for category_id in categories:
        idx_name = "category_{}".format(category_id)
        index_path = abs_path('data/{}.csv'.format(idx_name))

        print(file=fw)
        print_index(idx_name, 'template', 'dummy', {'path': index_path}, fw)

with open(abs_path('etc/mipt_search_test.conf'), 'w') as fw:
    print_index('template', '', 'template', template_index, fw)
    index_path = abs_path('data/category_0.csv')
    print_index("category_0", 'template', 'dummy', {'path': index_path}, fw)
