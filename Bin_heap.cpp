#include "Bin_heap.h"

//map the idx to the node to quickly target when decreaseKey
std::unordered_map<int, Node*> idx_node;
int popped[MAXV];

binHeap::binHeap() {
    Elements = new Node*[MAXV];
    Elements[0] = createNode(-1, -1);
    this->size = 0;
    capacity = MAXV;
}
binHeap::binHeap(int capacity) {
    Elements = new Node*[capacity];
    Elements[0] = createNode(-1, -1);
    this->capacity = capacity;
    this->size = 0;
}

//get size
int binHeap::get_size() {
    return this->size;
}
bool binHeap::isEmpty() {
    return this->size == 0;
}
//insert a vertex into the heap
void binHeap::insert(int idx, int dist) {
    Node* node = createNode(idx, dist);
    idx_node[idx] = node;
    this->size++;
    int i = this->size;
    // heap is full, error
    if (this->size == this->capacity) {
        std::cout << ("heap is full!") << std::endl;
        return;
    }
    //percolate up
    for (i; this->Elements[i/2]->dist > dist; i /= 2) {
        this->Elements[i] = this->Elements[i/2];
        //update the map
        idx_pos[this->Elements[i]->idx] = i;
    }
    this->Elements[i] = node;
    //update the map
    idx_pos[idx] = i;
}

Node* binHeap::deleteMin() {
    int i, child;
    //if the heap is empty, error
    if (this->isEmpty()) {
        std::cout << "the heap is empty!" << std::endl;
        return NULL;
    }
    Node* minNode = this->Elements[1];
    Node* last = this->Elements[this->size--];

    for (i = 1; i * 2 <= this->size; i = child) {
        //get the small child
        child = 2 * i;
        if (child != this->size && Elements[child+1]->dist < this->Elements[child]->dist)
            child++;

        if (last->dist > Elements[child]->dist) {
            Elements[i] = Elements[child];
            //update the map
            idx_pos[this->Elements[i]->idx] = i;
        } else {
            break;
        }
    }
    Elements[i] = last;
    //update the map
    idx_pos[Elements[i]->idx] = i;
    return minNode;
}

//input : index of the vertex in the graph and the new distance value
//decrease the distance of the vertex and then percolate up
void binHeap::decreaseKey(int idx, int newDist) {
    //index in the heap
    int i;
    int pos = idx_pos[idx];
    Node* node = Elements[pos];
    node->dist = newDist;
    //perculate up
    for (i = pos; Elements[i/2]->dist > newDist; i /= 2) {
        Elements[i] = Elements[i/2];
        //update the map
        idx_pos[Elements[i]->idx] = i;
    }
    Elements[i] = node;
    //update the map
    idx_pos[idx] = i;
}

//print heap for test
void binHeap::print_heap() {
    for (int i = 1; i <= this->size; i++) {
        std::cout << "index: " << Elements[i]->idx << " dist: " << Elements[i]->dist << std::endl;
    }
}

int binHeap::idx_dist(int idx) {
    int pos = idx_pos[idx];
    Node* node = Elements[pos];
    return node->dist;
}


int dijkstra_bin(int fromn,int ton) {
    binHeap heap;
    heap.insert(fromn,0);
    visited[fromn]=-1;
    Node* tempnode;
    int i = 0;
    while(!heap.isEmpty())
    {
        i++;
        tempnode = heap.deleteMin();
        popped[tempnode->idx] = 1;
        //get to destination
        if(tempnode->idx==ton)
        {
            std::cout << i << std::endl;
            return tempnode->dist;
        }
        //printf("%d\n",edges[tempnode->idx].size());    
        for(int i=0;i<edges[tempnode->idx].size();i++)
        {            
            if(visited[edges[tempnode->idx][i].y]==0)
            {
                heap.insert(edges[tempnode->idx][i].y,tempnode->dist+edges[tempnode->idx][i].w);
                visited[edges[tempnode->idx][i].y]=-1;
            }
            else if(!popped[edges[tempnode->idx][i].y]) {
                if (tempnode->dist+edges[tempnode->idx][i].w<heap.idx_dist(edges[tempnode->idx][i].y))
                    heap.decreaseKey(edges[tempnode->idx][i].y,tempnode->dist+edges[tempnode->idx][i].w);
            }
        }
    }
    return -1;
}


int main()
{
    printf("Starting test on Binary heap\n");
    //read the files
    freopen(DATA_PATH,"r",stdin);
    char s[500];
    for(int i=1;i<=4;i++)
        gets(s);
    int num,arc;
    char s1[10], s2[10];
    scanf("%s %s %d %d", s1, s2, &num,&arc);
    printf("vertex number : %d, edge number : %d\n",num,arc);
    for(int i=1;i<=3;i++)
        gets(s);
    int x,y,w;
    for(int i=1;i<=arc;i++)
    {
        scanf("a %d %d %d\n",&x,&y,&w);
        //printf("%d %d %d\n",x,y,w);
        add(x,y,w);
    }
    fclose(stdin);

    /*randomly get the query*/
    if (RANDOM == 0) {  //RANDOM is set to 0 by default to test the correctness of the result
        srand(SEED);       //set RANDOM to 1 in cfg.h to get new pairs.
    }
    FILE* fp = fopen(QUERY_PATH, "w");
    int start, end;
    
    // Change QUE_NUM in cfg.h to get different numbers of queries.
    for (int i = 1; i <= QUE_NUM; i++) {
        start = 1;
        end = rand() % num;
        from[i] = start;
        to[i] = end;
        fprintf(fp, "%lld %lld\n", start, end);
    }
    fclose(fp);

    double total_sec = 0.;
    for(int i=1;i<=QUE_NUM;i++)
    {
        memset(visited,0,sizeof visited);
        memset(popped,0,sizeof popped);
        clock_t start_time = clock();
        ans[i]=dijkstra_bin(from[i],to[i]);
        //printf("\n%d: %d",i,ans[i]);
        clock_t end_time = clock();
        double sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        total_sec += sec;
        //clear 
        for (std::unordered_map<int, Node*>::iterator it = idx_node.begin(); it != idx_node.end(); it++) {
            delete it->second;
        }
        idx_node.clear();
        printf("\r%3d%%", (int)(100L * i / QUE_NUM));
        fflush(stdout);
    }
    printf("Done!\nRunning time is : %f", total_sec);
    //write to output file
    freopen(BINARY_OUTPUT_PATH,"w",stdout);
    printf("Binary Heap:\n");
    printf("vertex number : %d, edge number : %d\n",num,arc);
    printf("Using %f seconds for %d times of query.\nQuery results:",total_sec,QUE_NUM);
    for(int i=1;i<=QUE_NUM;i++)
    {
        printf("\n%d: %d",i, ans[i]);
    }
}
// test

// int main() {
//     binHeap* h = new binHeap();
//     Node* node;
//     h->insert(2,2);
//     h->insert(4,4);
//     h->insert(3,3);
//     h->insert(5,5);
//     h->insert(6,6);
//     h->insert(9,9);
//     h->insert(8,8);
//     h->insert(7,7);

//     for (int i = 0; i < 1000000; i++) {
//         h->insert(2*i * pow(-1, i)+1, 2*i * pow(-1, i)-1);
//     }
//     h->print_heap();
//     std::cout << "---------------------" << std::endl;
//     std::cout << h->deleteMin()->dist << std::endl;
//     std::cout << h->deleteMin()->dist << std::endl;
//     std::cout << h->deleteMin()->dist << std::endl;
//     std::cout << h->deleteMin()->dist << std::endl;
//     std::cout << h->deleteMin()->dist << std::endl;
// }