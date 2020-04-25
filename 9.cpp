/*2015.7.17cyq*/
//关键路径
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
 
struct node{
	int early=0;		//最早可以开始的时间
	int late=2147483647;		//最晚必须开始的时间
	int inDegree=0;	//入度
	int outDegree=0;  //出度
    int key=0;//是否为关键活动
	vector<int> next;//后继结点
	vector<int> pre; //前驱结点
};

void init(vector<node> &graph, vector<vector<int> > &edge, const int num)
{
    for(int i=0;i<num;i++)//共M条边
    {
        int a,b,c;
		cin>>a>>b>>c;
		edge[a][b]=c;
		graph[a].next.push_back(b);
		graph[b].pre.push_back(a);
		graph[b].inDegree++;	//后继结点入度加1
		graph[a].outDegree++;	//前驱结点出度加1
	}
}

int earlySet(vector<node> &graph, const vector<vector<int> > edge, const int num)
{
    //从前往后计算每个结点最早可以开始的时间
	queue<int> q;
	int count=0; //记录入队的点的个数
	for(int i=1;i<=num;i++){
		if(graph[i].inDegree==0){
			graph[i].early=0;//开始时间为0
			q.push(i);	 //入度为0的结点进入队列
			count++;
		}
	}
	while(!q.empty()){
		for(int i=0;i<graph[q.front()].next.size();i++){
			if(graph[q.front()].early+edge[q.front()][graph[q.front()].next[i]]
             > graph[graph[q.front()].next[i]].early)
				graph[graph[q.front()].next[i]].early=
                graph[q.front()].early+edge[q.front()][graph[q.front()].next[i]];//最早开始时间为前驱结点花费时间最长的一条
			if(--graph[graph[q.front()].next[i]].inDegree==0)
            {
				q.push(graph[q.front()].next[i]);//新的入度为0结点
				count++;
			}	
		}
		q.pop();
	}

    return count;
}

void lateSet(vector<node> &graph, const vector<vector<int> > edge, const int time, const int num)
{
    //从后往前计算每个结点最晚必须开始的时间
    queue<int> q;
	for(int i=1;i<=num;i++){
	    if(graph[i].outDegree==0){
		    graph[i].late=time;
		    q.push(i);
	    }
    }
    while(!q.empty()){
	    for(int i=0;i<graph[q.front()].pre.size();i++){
		    if(graph[graph[q.front()].pre[i]].late
             > graph[q.front()].late-edge[graph[q.front()].pre[i]][q.front()])
			    graph[graph[q.front()].pre[i]].late
                 = graph[q.front()].late-edge[graph[q.front()].pre[i]][q.front()];//最晚开始时间为后继结点花费时间最长的一条
		    if(--graph[graph[q.front()].pre[i]].outDegree==0)
                q.push(graph[q.front()].pre[i]);//新的出度为0结点
		}
        q.pop();
    }
}

int doneTime(const vector<node> graph, const int num)
{
    int allTime=-1;//完成工程需要花费的最短总时间
	    for(int i=1;i<=num;i++){
		    if(graph[i].early>allTime)
			    allTime=graph[i].early;
	    }
	return allTime;
}

void keyNode(vector<node> &graph, const int num)
{
	for(int i=1;i<=num;i++){
	    if(graph[i].early==graph[i].late){
		    graph[i].key=1;
	    }
    }
}

void display(const vector<node> graph, const vector<vector<int> > edge, const int num)
{
    for(int i=1;i<=num;i++){
        if(graph[i].key)
	        for(int j=graph[i].next.size()-1;j>=0;j--)//倒序输出
            {
			    if(graph[graph[i].next[j]].key
                &&edge[i][graph[i].next[j]]==graph[graph[i].next[j]].early-graph[i].early)
                cout<<i<<"->"<<graph[i].next[j]<<endl;
	        }
    }
}
 
int main(){
	int N,M;
	cin>>N>>M;
	vector<vector<int> > edge(N+1,vector<int>(N+1,-1));//二维向量初始值为0，结点N个
	vector<node> graph(N+1);

    init(graph, edge, M);
    
    int count=earlySet(graph, edge, N);
	if(count!=N)
		cout<<0<<endl;//出现循环
	else
    {
	    int time=doneTime(graph,N);
        lateSet(graph, edge, time, N);
        
        cout<<time<<endl;
        if(time)
        {
            keyNode(graph,N);
            display(graph,edge,N);
        }   
    }
	
	return 0;
}

