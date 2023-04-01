#include<iostream>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;
vector <int> G[1000];
float eb[10][10]={0};
int edges,loop;
int shortpathf(int s,int n,float arr[]){
	int visited[n]={0};
	visited[s]=1;
	int d[n],p[n];
	d[s]=0;
	p[s]=-1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int v=q.front();
		q.pop();
		for(int u: G[v])
		{
			if(visited[u]){
				int i=d[u];
				arr[u]=i;
				i++;
				continue;
			}
			if (!visited[u])
			{
				visited[u]=1;
				q.push(u);
				d[u]=d[v]+1;
				p[u]=v;
			}
		}
	}
}
int cal(int s,int n,float a[],float b[],float c[]){
	int visited[n]={0};
	visited[s]=1;
	int d[n],p[n];
	d[s]=0;
	p[s]=-1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int v=q.front();
		q.pop();
		for(int u: G[v])
		{
				a[u]=1;
				b[u]=1;
				c[u]=1;
				d[u]=1;
			if(visited[u]){
				eb[u][v]=(a[v]/a[u])+(b[v]/b[u])+(c[v]/c[u])+(d[v]/d[u]);
				eb[u][v]+=eb[u+1][v+1];
				continue;
			}
			if (!visited[u])
			{
				visited[u]=1;
				q.push(u);
				d[u]=d[v]+1;
				if(u!=v){
					eb[u][v]=(a[v]/a[u])+(b[v]/b[u])+(c[v]/c[u])+(d[v]/d[u]);
					eb[u][v]+=eb[u+1][v+1];
				}
				p[u]=v;
			}
		}
	}
}
int eadgebetweenes(int n){
			float a[30]={0};
			float b[30]={0};
			float c[30]={0};
			float d[30]={0};	
		shortpathf(0,n,a);
		shortpathf(1,n,b);
		shortpathf(2,n,c);
		shortpathf(3,n,d);
		cout<<endl;
		cal(0,n,a,b,c);
		cal(1,n,a,b,c);
		cal(2,n,a,b,c);
		cal(3,n,a,b,c);
		
}

void removeE(){
	int max=eb[0][0];
	int q;
	int w;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(eb[i][j]!=0 && eb[i][j]!=INFINITY){
				if(eb[i][j]>max){
					max=eb[i][j];
				}
			}
		}
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(eb[i][j]!=0 && eb[i][j]!=INFINITY){
				if(eb[i][j]==max){
					eb[i][j]=0;
					q=i;
					w=j;
					cout<<"change"<<endl;
					break;
				}
			}
		}
	}
	for (int k = 0; k < G[w].size(); k++) {
        if (G[w][k] == q) {
        	cout<<"Remove eadge : "<<w<<" to "<<q<<endl;
            G[w].erase(G[w].begin() + k);
            break;
        }
    }
	for (int k = 0; k < G[q].size(); k++) {
        if (G[q][k] == w) {
        	cout<<"Remove eadge : "<<q<<" to "<<w<<endl;
            G[q].erase(G[q].begin() + k);
            loop=loop-1;
            cout<<"edge "<<loop<<endl;
            break;
        }
    }
}

void girvan(int n){
	eadgebetweenes(n);
	removeE();
}

int main(){
	int n;
	cout<<"number of nodes ";
cin>>n;
	cout<<"number of edges ";
cin>>edges;
loop=edges;
while(edges--)
{
	int x,y;
	cout<<" two nodes attached "<<endl;
	cin>>x>>y;
	G[x].push_back(y);
	G[y].push_back(x);
	}

		girvan(n);
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(eb[i][j]!=0 && eb[i][j]!=INFINITY){
				cout<<"i : "<<i<<"  j: "<<j<<" betweenes: "<<eb[i][j]<<endl;
			}
		}
	}
}
