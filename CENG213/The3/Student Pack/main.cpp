#include "Graph.h"
#include <iostream>
/*You can add additional libraries here to read and process the dataset*/
#include <fstream> // file read/write

using namespace std;

// tester
int main() {

    /*
    // read input file
    ifstream inputF;

    // Metal trade Graph
    Graph graph;

    fstream file("world_trade.txt");

    string vertices;
    getline(file, vertices, '\t'); // skip header
    getline(file, vertices, '\n'); // number of vertices

    int numvertices = atoi( vertices.c_str() );
    HashTable<int, Node> nodeTable;

    // Build the graph from the txt input file
    for (int i = 0; i < numvertices; i++) {

        string vid, country, continent, gdp;
        getline(file, vid, '\t');
        getline(file, country, '\t');
        getline(file, continent, '\t');
        getline(file, gdp, '\n');

        Node node(atoi(vid.c_str()), country, continent, atol(gdp.c_str()));
        nodeTable.Insert(node.getVid(), node);

        graph.addNode(node);
    }
    getline(file, vertices, '\n'); // skip header

    // create connections
    string line;
    while (getline(file, line)) {
        int pos = line.find("\t");
        int vid1 = atoi(line.substr(0, pos).c_str());

        line = line.substr(pos+1);
        pos = line.find("\t");
        int vid2 = atoi(line.substr(0, pos).c_str());

        line = line.substr(pos+1);
        long import = atol(line.c_str());

        graph.addConnection(nodeTable.Get(vid1), nodeTable.Get(vid2), import);
    }

    file.close();
	*/
	
	// YOU CAN WRITE YOUR TEST CASES BELOW
    
	Graph deneme;
    list<Node> returnedList;
    list<Node>::iterator itr;
    
    Node a(1, "a", "Kıta1", 50);
    Node b(2, "b", "Kıta2", 500);
    Node c(3, "c", "Kıta3", 25);
    Node d(4, "d", "Kıta4", 30);
    Node e(5, "e", "Kıta5", 30);
    Node f(6, "f", "Kıta6", 30);
    Node g(7, "g", "Kıta6", 30);
    Node h(8, "h", "Kıta6", 30);
    Node i(9, "i", "Kıta6", 30);
    Node j(10, "j", "Kıta6", 30);
    Node k(11, "k", "Kıta6", 30);
    deneme.addNode(a);
    deneme.addNode(b);
    deneme.addNode(c);
    deneme.addNode(d);
    deneme.addNode(e);
    deneme.addNode(f);
    deneme.addNode(g);
    deneme.addNode(h);
    deneme.addNode(i);
    deneme.addNode(j);
    deneme.addNode(k);


    
    deneme.addConnection(a, b, 3);
    deneme.addConnection(b, c, 3);
    deneme.addConnection(c, a, 3);
    

    //deneme.addConnection(node2, node3, 1);
    //deneme.addConnection(node1, node3, 1);
    //std::cout << deneme.isCyclic() << "\n";
    
    
    list<string> pathList;
    list<string>::iterator itrPath;

    //pathList = graph.getBFSPath(Node(76, "Turkey", "Europe", 2763), Node(30, "Honduras", "North America",700));
    pathList = deneme.findLeastCostPath(a, c);
    for (itrPath = pathList.begin(); itrPath != pathList.end(); itrPath++)
    {
        std::cout << *itrPath << " ";
    }
    std::cout << "\n";
    
   /*
        Graph graph;

        Node a = Node(1, "Algeria", "Africa", 1209);
        Node b = Node(2, "Argentina", "South America", 8042);
        Node c = Node(4, "Austria", "Europe", 28942);
        Node d = Node(5, "Barbados", "South America", 7053);
        Node e = Node(6, "Bangladesh", " Asia", 272);
        Node f = Node(7, "Belgium", "Lux.Europe", 27129);
        Node g = Node(12, "Chile", "South America", 4589);
        Node h = Node(14, "Colombia", "South America", 2089);
        Node j = Node(15, "Croatia", "Europe", 4187);
        Node k = Node(16, "Northern Cyprus", "Europe", 11818);
        Node l = Node(17, "Czech", "Europe", 4922);
        Node m = Node(18, "Denmark", "Europe", 33121);
        Node n = Node(20, "Egypt", "Africa", 970);
        Node o = Node(21, "El Salvador", "North America", 1675);
        Node p = Node(22, "Fiji", "Oceania", 2604);
        Node r = Node(24, "Germany", "Europe", 26458);
        Node s = Node(25, "French, Guiana", "South America", 11415);
        Node t = Node(27, "Greece", "Europe", 10900);
        Node w = Node(28, "Guadeloupe", "South America", 9204);
        Node x = Node(29, "Guatemala", "North America", 1469);
        Node y = Node(30, "Honduras", "North America", 700);
        Node z = Node(31, "Hong Kong", "Asia", 22372);
        Node q = Node(32, "Hungary", "Europe", 4274);
        Node v = Node(33, "Iceland", "Europe", 26006);
        Node a1 = Node(37, "Israel", "Asia", 16506);
        Node b1 = Node(38, "Italy", "Europe", 18975);
        Node c1 = Node(39, "Japan", "Asia", 40920);
        Node d1 = Node(42, "Kuwait", "Asia", 15717);
        Node e1 = Node(43, "Latvia", "Europe", 1754);
        Node f1 = Node(44, "Madagascar", "Africa", 114);
        Node g1 = Node(48, "Mexico", "North America", 3140);
        Node h1 = Node(49, "Morocco", "Africa", 1270);
        Node j1 = Node(50, "Netherlands", "Europe", 25769);
        Node k1 = Node(53, "Norway", "Europe", 33708);
        Node l1 = Node(54, "Oman", "Asia", 6382);
        Node m1 = Node(55, "Pakistan", "Asia", 502);
        Node n1 = Node(56, "Panama", "North America", 3005);
        Node o1 = Node(57, "Paraguay", "South America", 1860);
        Node p1 = Node(62, "Moldava.Rep.Of", "Europe", 329);
        Node r1 = Node(63, "Reunion", "Africa", 11856);
        Node s1 = Node(66, "Singapore", "Asia", 25645);
        Node t1 = Node(71, "Sweden", "Europe", 26296);
        Node w1 = Node(72, "Switzerland", " Europe", 43034);
        Node x1 = Node(76, "Turkey", "Europe", 2763);
        Node y1 = Node(77, "United Kingdom", "Europe", 18991);
        Node z1 = Node(78, "United States", "North America", 26341);
        Node q1 = Node(79, "Uruguay", "South America", 5526);
        Node v1 = Node(80, "Venezuela", " South America", 3496);
        graph.addNode(a);
        graph.addNode(b);
        graph.addNode(c);
        graph.addNode(d);
        graph.addNode(e);
        graph.addNode(f);
        graph.addNode(g);
        graph.addNode(h);
        graph.addNode(j);
        graph.addNode(k);
        graph.addNode(l);
        graph.addNode(m);
        graph.addNode(n);
        graph.addNode(o);
        graph.addNode(p);
        graph.addNode(r);
        graph.addNode(s);
        graph.addNode(t);
        graph.addNode(w);
        graph.addNode(x);
        graph.addNode(y);
        graph.addNode(z);
        graph.addNode(q);
        graph.addNode(v);
        graph.addNode(a1);
        graph.addNode(b1);
        graph.addNode(c1);
        graph.addNode(d1);
        graph.addNode(e1);
        graph.addNode(f1);
        graph.addNode(g1);
        graph.addNode(h1);
        graph.addNode(j1);
        graph.addNode(k1);
        graph.addNode(l1);
        graph.addNode(m1);
        graph.addNode(n1);
        graph.addNode(o1);
        graph.addNode(p1);
        graph.addNode(r1);
        graph.addNode(s1);
        graph.addNode(t1);
        graph.addNode(w1);
        graph.addNode(x1);
        graph.addNode(y1);
        graph.addNode(z1);
        graph.addNode(q1);
        graph.addNode(v1);

        graph.addConnection(a, b, 1000);
        graph.addConnection(a, s1, 1234);
        graph.addConnection(a, y1, 21432);
        graph.addConnection(b, m1, 2323);
        graph.addConnection(c, v1, 23232);
        graph.addConnection(g, g1, 100000);
        graph.addConnection(b, j1, 238924);
        graph.addConnection(j1, p1, 1232);
        graph.addConnection(p1, a, 344983);
        graph.addConnection(k1, l1, 39483);
        graph.addConnection(x1, z1, 100000);
        graph.addConnection(x1, t1, 23232);
        graph.addConnection(a1, x1, 66666);
        graph.addConnection(a1, r, 1232323);
        graph.addConnection(z1, x1, 24893);
        graph.addConnection(x1, k, 1);
        graph.addConnection(t, a1, 6867);
        graph.addConnection(d, e, 3247);
        graph.addConnection(e1, f, 4567);
        graph.addConnection(k, l, 123872);
        graph.addConnection(d, o, 3247);
        graph.addConnection(d, p, 4567);
        graph.addConnection(d, r, 123872);
        graph.addConnection(k, p, 123452);
        graph.addConnection(k, n, 1872);

        std::list<Node> out;
        //AdjNodes
        out = graph.getAdjacentNodes(a);
        std::cout << "adjNodes of : " << a.getCountry() << std::endl;
        auto it1 = out.begin();
        for (it1; it1 != out.end(); it1++)
        {
            std::cout << it1->getCountry() << std::endl;
        }
        */
    /*
    returnedList = deneme.getAdjacentNodes(node1);
    for (itr = returnedList.begin(); itr != returnedList.end(); itr++)
    {
        std::cout << itr->getCountry() << " ";
    }
    std::cout << "\n";
    */
    //std::cout << graph.getTotalImports(Node(15, "Algeria", "Africa", 1209)) << "\n";
    return 0;
}
