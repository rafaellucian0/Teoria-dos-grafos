#include <bits/stdc++.h>
using namespace std;

typedef struct graph{
    int n, m;
    vector<vector<int>> edges;
} Graph;

void bellmanford(Graph G, int comeco, ostream& out){
    vector<int> dist(G.n, INT_MAX);

    dist[comeco] = 0;

    for(int i = 0; i < G.n; i++){
        for(auto ed: G.edges){
            int u = ed[0];
            int v = ed[1];
            int p = ed[2];
            if (dist[u] != INT_MAX && dist[u] + p < dist[v])
                dist[v] = dist[u] + p;
        }
    }

    for(auto ed: G.edges){
        int u = ed[0];
        int v = ed[1];
        int p = ed[2];
        if (dist[u] != INT_MAX && dist[u] + p < dist[v])
        {
            cout << "O grafo tem um ciclo negativo";
            return;
        }
    }

    for(int i = 0; i < G.n; i++){
        if (dist[i] == INT_MAX){
            out << i + 1 << ":-1 ";
        }
        else{
            out << i + 1 << ":" << dist[i] << " ";
        }
    }
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    int inicial = 0;

    for(int i = 0; i < argc; i++){
        string arg = argv[i];

        if(strcmp(argv[i], "-h") == 0){
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        }
        else if(arg == "-o" && i < argc - 1){
            output_file = argv[++i];
        } 
        else if(arg == "-f" && i < argc - 1){
            input_file = argv[++i];
        }
        else if(arg == "-i" && i < argc - 1){
            inicial = atoi(argv[i+1]);
            inicial--;
        }
    }

    ifstream fin(input_file);
    if(fin.fail() == 1){
        cout << "Arquivo não encontrado";
        return 1;
    }
    if(input_file == ""){
        cerr << "Arquivo de entrada nao especificado. Use o parametro -f." << endl;
        return 1;
    }

    if(!fin){
        cerr << "Nao foi possivel abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int qtd_v, qtd_a;
    fin >> qtd_v >> qtd_a;

    if(inicial >= qtd_v || inicial < 0){
        cout << "Vertice inicial nao pertence ao grafo";
        return 2;
    }

    Graph G;
    G.n = qtd_v;
    G.m = qtd_a;
    for(int i = 0; i < qtd_a; i++){
        int v1, v2, p;
        fin >> v1 >> v2 >> p;
        G.edges.push_back({v1 - 1, v2 - 1, p});
    }


    fin.close();

    if(!output_file.empty()){
        ofstream fout(output_file);
        if(fout.fail() == 1){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }
        bellmanford(G, inicial, fout);
        fout.close();
    }
    bellmanford(G, inicial, cout);
	return 0;
}