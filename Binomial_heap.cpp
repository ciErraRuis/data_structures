#include "Binomial_heap.h"

std::unordered_map<int, bNode*> idx_node;
int popped[MAXQ], outed[MAX_SIZE];
//class of binomial heap

	BinomialHeap::BinomialHeap() {
		min_node = nullptr;
		count = 0;
		trees.clear();
	}

	//return whether the heap is empty
	bool BinomialHeap::is_empty() {
		return min_node == nullptr;
	}

	//insert a node to the heap
	void BinomialHeap::insert(int idx, int value) {
		bNode* node = new bNode(value, idx);
		idx_node[idx] = node;
		BinomialHeap heap;
		heap.trees.push_back(node);
		merge(heap);
	}

	//get the mininum value from the heap
	int BinomialHeap::get_min() {
		return min_node->value;
	}

	//pop out the mininun node from the heap
	bNode* BinomialHeap::extract_min() {
		bNode* minNode = min_node;
		trees.erase(remove(trees.begin(), trees.end(), minNode), trees.end());
		BinomialHeap heap;
		heap.trees = minNode->children;
		merge(heap);
		_find_min();
		count -= 1;
		return minNode;
	}

	void BinomialHeap::merge(BinomialHeap& other_heap) {
		trees.insert(trees.end(), other_heap.trees.begin(), other_heap.trees.end());
		count += other_heap.count;
		_find_min();
	}

	void BinomialHeap::_find_min() {
		min_node = nullptr;
		for (bNode* tree : trees) {
			if (min_node == nullptr || tree->value < min_node->value) {
				min_node = tree;
			}
		}
	}

	//renew a node, which has a smaller distance
	void BinomialHeap::decrease_key(bNode* node, int new_value) {
		if (new_value > node->value) {
			throw invalid_argument("New value is greater than the current value");
		}
		node->value = new_value;
		_bubble_up(node);
	}

	void BinomialHeap::delete_node(bNode* node) {
		decrease_key(node, INT_MIN);
		extract_min();
	}

	void BinomialHeap::_bubble_up(bNode* node) {
		bNode* parent = node->parent;
		while (parent != nullptr && node->value < parent->value) {
			swap(node->value, parent->value);
			node = parent;
			parent = node->parent;
		}
	}

	void BinomialHeap::_link(bNode* tree1, bNode* tree2) {
		if (tree1->value > tree2->value) {
			swap(tree1, tree2);
		}
		tree2->parent = tree1;
		tree1->children.push_back(tree2);
		tree1->degree += 1;
	}

	void BinomialHeap::_consolidate() {
		int max_degree = static_cast<int>(floor(log2(count))) + 1;
		vector<bNode*> degree_to_tree(max_degree + 1, nullptr);

		while (!trees.empty()) {
			bNode* current = trees[0];
			trees.erase(trees.begin());
			int degree = current->degree;
			while (degree_to_tree[degree] != nullptr) {
				bNode* other = degree_to_tree[degree];
				degree_to_tree[degree] = nullptr;
				if (current->value < other->value) {
					_link(current, other);
				} else {
					_link(other, current);
					current = other;
				}
				degree++;
			}
			degree_to_tree[degree] = current;
		}

		min_node = nullptr;
		trees.clear();
		for (bNode* tree : degree_to_tree) {
			if (tree != nullptr) {
				trees.push_back(tree);
				if (min_node == nullptr || tree->value < min_node->value) {
					min_node = tree;
				}
			}
		}
	}
	int BinomialHeap::size() {
		return count;
	}

int dijkstra_binomial(int fromn,int ton)
{
    BinomialHeap heap;
    memset(visited,0,sizeof visited);//reset visited[] to 0, because we need to run thousands of times in dijkstra.
    memset(dis,0,sizeof dis);
	memset(outed,0,sizeof outed);
	dis[fromn]=0;
	heap.insert(fromn,0);//insert the initial node, the root of the heap
    visited[fromn]=-1;
    bNode* tempnode;
	int i = 0;
    while(!heap.is_empty())//keep searching until the heap is empty
    {
		i++;
        tempnode = heap.extract_min();//pop the root out
		//printf("'%d'\n",tempnode->index);
		if(outed[tempnode->index]==-1)
			continue;
		outed[tempnode->index]=-1;
        if(tempnode->index==ton)//if it is the node we want
        {
            while(!heap.is_empty())//clean up the heap and then return.
                heap.extract_min();
            return tempnode->value;
        }
        //printf("%d\n",edges[tempnode->idx].size());    
        for(int i=0;i<edges[tempnode->index].size();i++)//traverse the nodes which build an edge with the current node.
        //if(outed[edges[tempnode->index][i].y]!=-1)
		{
            if(visited[edges[tempnode->index][i].y]==0)//if not visited, push in and visited
            {
                heap.insert(edges[tempnode->index][i].y,tempnode->value+edges[tempnode->index][i].w);
                visited[edges[tempnode->index][i].y]=-1;
				dis[edges[tempnode->index][i].y]=tempnode->value+edges[tempnode->index][i].w;
            }
            if(  visited[edges[tempnode->index][i].y]==-1
               &&tempnode->value+edges[tempnode->index][i].w<dis[edges[tempnode->index][i].y])//if visited but with a shorter path, update it.
            {	
				heap.insert(edges[tempnode->index][i].y,tempnode->value+edges[tempnode->index][i].w);
				dis[edges[tempnode->index][i].y]=tempnode->value+edges[tempnode->index][i].w;
			}
        }
    }
    return -1;//only when there is no way from fromn to ton.
}


int main()
{
    printf("Starting test on Binomial heap\n");
    freopen(DATA_PATH,"r",stdin);//open the dataset
    char s[500];
    for(int i=1;i<=4;i++)
        gets(s);
    int num,arc;
    char s1[10], s2[10];
    scanf("%s %s %d %d", s1, s2, &num,&arc);
    printf("vertex number : %d, edge number : %d\n",num,arc);
    //read the dataset
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
    if (RANDOM == 0) {
        srand(SEED);
    }
    FILE* fp = fopen(QUERY_PATH, "w");
    int start, end;
    for (int i = 1; i <= QUE_NUM; i++) {
        start = rand() % num;
        end = rand() % num;
        from[i] = start;
        to[i] = end;
        fprintf(fp, "%d %d\n", start, end);
    }
    fclose(fp);

    //printf("Enter Dijkstra");
    double total_sec = 0.;
    for(int i=1;i<=QUE_NUM;i++)
    {
        memset(visited,0,sizeof visited);//reset visited[] to 0, because we need to run thousands of times in dijkstra.
        clock_t start_time = clock();
        ans[i]=dijkstra_binomial(from[i],to[i]);
        //printf("\n%d: %d",i,ans[i]);
        clock_t end_time = clock();
        double sec = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        total_sec += sec;
        //clear 
        for (std::unordered_map<int, bNode*>::iterator it = idx_node.begin(); it != idx_node.end(); it++) {
            delete it->second;
        }
        idx_node.clear();
        printf("\r%3d%%", (int)(100L * i / QUE_NUM));
        fflush(stdout);
    }
    printf("Done!\nTotal time: %f", total_sec);
    //output
    freopen(SKEW_OUTPUT_PATH,"w",stdout);
    printf("Binomial Heap:\n");
    printf("vertex number : %d, edge number : %d\n",num,arc);
    printf("Using %f seconds for %d times of query.\nQuery results:",total_sec,QUE_NUM);
    for(int i=1;i<=QUE_NUM;i++)
    {
        printf("\n%d: %d",i,ans[i]);
    }
}