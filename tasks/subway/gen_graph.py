import pandas as pd
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import warnings
import random
import itertools
import dsu
import io

warnings.filterwarnings("ignore")

street_names = set(pd.read_csv('street-names.csv')['StreetName'])
street_names

def gen_graph(n_stations: list):
    G = nx.Graph()
    names = random.sample(street_names, sum(n_stations))
    assert len(names) == len(set(names))
    lines_names = list([i.title() for i in names])
    node_names = [lines_names[sum(n_stations[:c]):sum(n_stations[:c]) + stations] for c, stations in zip(itertools.count(), n_stations)]
    lines = []
    for c, stations in zip(itertools.count(), n_stations):
        G.add_nodes_from(node_names[c], color = c / (len(n_stations) - 1))
        for f, t in zip(node_names[c][:-1], node_names[c][1:]):
            G.add_edge(f, t, length = random.randint(5, 8), weight = 4, color = c / (len(n_stations) - 1))
    c = 0
    d = dsu.DSU(len(n_stations))
    while c != len(n_stations)-1:
        i, j = random.randint(0, len(n_stations) - 1), random.randint(0, len(n_stations) - 1)
        if d.get(i) != d.get(j):
            f, t = random.choice(node_names[i]), random.choice(node_names[j])
            G.add_edge(f, t, length = random.randint(2, 5), weight = 2, color = -1)
            d.join(i, j)
            c+=1

    return G


def gen_svg_from_graph(G, pos):
    cmap = plt.cm.get_cmap('gist_rainbow')
    node_colors = [cmap(i[1]['color']) if i[1]['color'] != -1 else (0.2, 0.2, 0.2, 1.0) for i in G.nodes(data=True)]
    edge_colors = [cmap(i[2]['color']) if i[2]['color'] != -1 else (0.2, 0.2, 0.2, 1.0) for i in G.edges(data=True)]
    edge_labels = {(i[0], i[1]): i[2]['length'] for i in G.edges(data=True)}

    plt.figure(figsize=(50, 50)) 
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    nx.draw(G, pos, 
                  with_labels=True, 
                  node_size=300,
                  node_color=node_colors,
                  edge_color=edge_colors,
                  width=10.0)
    t = io.StringIO()
    plt.savefig(t, format='svg')
    t.seek(0)
    return t.read()



def find_ans(G, start):
    return nx.single_source_dijkstra(G, start)
    
def gen_task(g):
    G = gen_graph(g)
    start = random.choice(list(G.nodes()))
    ans = find_ans(G, start)[0]
    pos = nx.kamada_kawai_layout(G, weight='weight')
    svg = gen_svg_from_graph(G, pos)
    return (svg, pos, start, ans)































