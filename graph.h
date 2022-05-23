#include"testlib.h"


class Tree {
	private:
		/*节点数,默认为1；根，默认为0；根的父亲表示，默认是-1；初始节点，默认为1*/
		int node,root,rootfather,firstnode;
		int type;
		/*
		类型：
		0：完全随机
		1：菊花
		2：链
		*/
		std::vector<std::pair<int,int>>edge;/*边*/
		std::vector<int> father;/*父亲*/
	public:
		Tree() {
			node=1;
			root=0;
			rootfather=-1;
			type=0;
			firstnode=1;
		}
		void InitTree(int n,int rt,int fin,int rtf=-1) {
			node=n;
			root=rt;
			firstnode=fin;
			rootfather=rtf;
			father.resize(n);
			edge.clear();
		}
		void SetNode(int n) {
			node=n;
			father.resize(node);
		}
		void SetRoot(int rt) {
			root=rt-firstnode;
		}
		void SetRootFather(int rtf) {
			rootfather=rtf;
		}
		void SetType(int tp) {
			type=tp;
		}
		void SetFirstNode(int fin) {
			firstnode=fin;
		}
		std::vector<int> GetFather() {
			return father;
		}
		std::vector<std::pair<int,int>> GetEdge() {
			return edge;
		}
		/*生成随机的树*/
		std::vector<int> GenRandomTree(int t) {
			std::vector<int> p(node),f(node),fa(node);
			for(int i=0; i<node; i++)	{
				p[i]=i;
			}
			std::swap(p[0],p[root]);
			shuffle(p.begin()+1,p.end());
			for(int i=1; i<node; i++) {
				f[i]=rnd.wnext(i,t);
			}
			for(int i=0; i<node; i++) {
				fa[p[i]]=p[f[i]];
			}
			fa[root]=rootfather;
			return fa;
		}
		/*生成树的父亲和边*/
		void GenTree() {
			father.resize(node);
			edge.clear();
			if(type==0) {
				father=GenRandomTree(0);
			} else if(type==1) {
				father=GenRandomTree(-1000000);
			} else if(type==2) {
				father=GenRandomTree(1000000);
			}
			for(int i=0; i<node; i++) {
				if(i==root)	continue;
				father[i]+=firstnode;
			}
			for(int i=0; i<node; i++) {
				if(i==root)	continue;
				int w=rnd.next(2);
				if(w) {
					edge.push_back({i+firstnode,father[i]});
				} else {
					edge.push_back({father[i],i+firstnode});
				}
			}
		}
		/*指定类型的生成树*/
		void GenTree(int tp) {
			type=tp;
			GenTree();
		}
} tree;

class Graph {
	private:
		int node/*点数*/,firstnode/*初始节点，默认为1*/;
		int edgecount;/*边数*/
		std::vector<std::pair<int,int>>edge;/*边*/
		int direction;
		/*
		0：无向
		1：有向
		默认无向图
		*/
		int multiply_edge;
		/*
		0：无重边
		1：有重边
		默认无重边
		*/
		int self_loop;
		/*
		0：无自环
		1：有自环
		默认无自环
		*/
		int connect;
		/*
		0：不保证连通
		1：保证连通
		默认不保证连通
		*/
	public:
		Graph() {
			node=0;
			firstnode=1;
			edgecount=node-1;
			direction=0;
			multiply_edge=0;
			self_loop=0;
			connect=0;
		}
		void SetNode(int n) {
			node=n;
		}
		void SetEdge(int m) {
			edgecount=m;
		}
		void SetDirection(int dir) {
			direction=dir;
		}
		void SetMultiplyEdge(int x) {
			multiply_edge=x;
		}
		void SetSelfLoop(int x) {
			self_loop=x;
		}
		void SetConnect(int x) {
			connect=x;
		}
		void GenRandomGraph() {
			edge.clear();
			int m=edgecount;
			if(connect) {
				tree.SetNode(node);
				tree.SetFirstNode(firstnode);
				tree.GenTree();
				edge=tree.GetEdge();
				m-=(node-1);
			}
			std::map<std::pair<int,int>,int> mp;
			for(auto x:edge){
				if(direction) {
					mp[{x.first,x.second}]=1;
				}
				else{
					mp[{x.first,x.second}]=1;
					mp[{x.second,x.first}]=1;
				}
			}
			while(m--) {
				int u=rnd.next(node),v=rnd.next(node);
				if(self_loop==0 && multiply_edge==0) {
					while(u==v || mp[ {u,v}]) {
						u=rnd.next(node);
						v=rnd.next(node);
					}
				} else if(self_loop==0) {
					while(u==v)	{
						u=rnd.next(node);
						v=rnd.next(node);
					}
				} else if(multiply_edge==0) {
					while(mp[ {u,v}]) {
						u=rnd.next(node);
						v=rnd.next(node);
					}
				}
				u+=firstnode;
				v+=firstnode;
				if(direction) {
					mp[ {u,v}]=1;
				} else {
					mp[ {u,v}]=1;
					mp[ {v,u}]=1;
				}
				edge.push_back({u,v});
			}
		}
		std::vector<std::pair<int,int>> GetEdge(){
			return edge;
		}
} graph;
