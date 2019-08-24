import itertools
import random
import warnings
import uuid

import matplotlib.pyplot as plt
import networkx as nx
import pandas as pd
import os
import json

from subway import app
import subway.dsu

warnings.filterwarnings("ignore")


street_names = set(pd.read_csv(os.path.join(app.root_path, "street-names.csv"))['StreetName'])


def gen_graph(n_stations: list):
    G = nx.Graph()
    names = random.sample(street_names, sum(n_stations))
    assert len(names) == len(set(names))
    lines_names = list([i.title() for i in names])
    node_names = [lines_names[sum(n_stations[:c]):sum(n_stations[:c]) + stations] for c, stations in
                  zip(itertools.count(), n_stations)]
    for c, stations in zip(itertools.count(), n_stations):
        G.add_nodes_from(node_names[c], color=c / (len(n_stations) - 1))
        for f, t in zip(node_names[c][:-1], node_names[c][1:]):
            G.add_edge(f, t, length=random.randint(5, 8), weight=4, color=c / (len(n_stations) - 1))
    c = 0
    d = subway.dsu.DSU(len(n_stations))
    while c != len(n_stations) - 1:
        i, j = random.randint(0, len(n_stations) - 1), random.randint(0, len(n_stations) - 1)
        if d.get(i) != d.get(j):
            f, t = random.choice(node_names[i]), random.choice(node_names[j])
            G.add_edge(f, t, length=random.randint(2, 5), weight=2, color=-1)
            d.join(i, j)
            c += 1

    return G


def gen_svg_from_graph(g, pos, path):
    cmap = plt.cm.get_cmap('rainbow')
    node_colors = [cmap(i[1]['color']) if i[1]['color'] != -1 else (0.2, 0.2, 0.2, 1.0) for i in g.nodes(data=True)]
    edge_colors = [cmap(i[2]['color']) if i[2]['color'] != -1 else (0.2, 0.2, 0.2, 1.0) for i in g.edges(data=True)]
    edge_labels = {(i[0], i[1]): i[2]['length'] for i in g.edges(data=True)}
    fig, ax = plt.subplots(figsize=(35, 35), frameon=False)
    nx.draw_networkx_edge_labels(g, pos, edge_labels=edge_labels, ax=ax)
    nx.draw_networkx(g, pos,
            with_labels=True,
            node_size=300,
            node_color=node_colors,
            edge_color=edge_colors,
            width=10.0,
            ax=ax)
    ax.axis([-1.05, 1.05, -1.05, 1.05])
    ax.grid(True, which='both')
    fig.savefig(path, format='svg', bbox_inches = 'tight', pad_inches = 0)


def find_ans(G, start):
    return nx.single_source_dijkstra(G, start, weight="length")


def gen_task(g):
    if not os.path.exists("tasks"):
        os.mkdir("tasks")
    id = str(uuid.uuid4())
    path = os.path.join(app.config["SVG_DIR"], id + ".svg")
    json_path = os.path.join(app.config["SVG_DIR"], id + ".json")
    G = gen_graph(g)
    start = random.choice(list(G.nodes()))
    ans = find_ans(G, start)[0]
    pos = {i: tuple(j) for i, j in nx.kamada_kawai_layout(G, weight='weight').items()}
    gen_svg_from_graph(G, pos, path)
    with open(json_path, "w") as f:
        json.dump({"id": id, "start": start, "pos": pos, "ans": ans}, f)
    return id
