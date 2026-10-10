//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


template<class T>
class TreapVector{
	struct Node{
		T val;
		int l=-1,r=-1,sz=1;
		uint32_t pri;
		template<class U>
		Node(U&& val,uint32_t pri):val(forward<U>(val)),pri(pri){}
	};

	vector<Node> tr;
	vector<int> free_id;
	int root=-1;

	uint64_t rnd=chrono::steady_clock::now().time_since_epoch().count();

	uint32_t rng(){
		rnd^=rnd<<7;
		rnd^=rnd>>9;
		return (uint32_t)rnd;
	}

	int sz(int t) const{
		return t==-1 ? 0 : tr[t].sz;
	}

	void pull(int t){
		tr[t].sz=1+sz(tr[t].l)+sz(tr[t].r);
	}

	bool higher(int a,int b) const{
		if(tr[a].pri!=tr[b].pri)return tr[a].pri>tr[b].pri;
		return a>b;
	}

	// 先頭 k 個 / それ以降 に分割
	void split(int t,int k,int& a,int& b){
		if(t==-1){
			a=b=-1;
			return;
		}

		if(sz(tr[t].l)>=k){
			split(tr[t].l,k,a,tr[t].l);
			pull(t);
			b=t;
		}else{
			split(tr[t].r,k-sz(tr[t].l)-1,tr[t].r,b);
			pull(t);
			a=t;
		}
	}

	int merge(int a,int b){
		if(a==-1) return b;
		if(b==-1) return a;

		if(higher(a,b)){
			tr[a].r=merge(tr[a].r,b);
			pull(a);
			return a;
		}else{
			tr[b].l=merge(a,tr[b].l);
			pull(b);
			return b;
		}
	}

	template<class U>
	int new_node(U&& val){
		uint32_t pri=rng();

		if(free_id.empty()){
			tr.emplace_back(forward<U>(val),pri);
			return (int)tr.size()-1;
		}

		int id=free_id.back();
		free_id.pop_back();

		tr[id].val=forward<U>(val);
		tr[id].l=tr[id].r=-1;
		tr[id].sz=1;
		tr[id].pri=pri;

		return id;
	}

	// pos に x を挿入
	int insert_node(int t,int pos,int x){
		if(t==-1) return x;

		if(higher(x,t)){
			split(t,pos,tr[x].l,tr[x].r);
			pull(x);
			return x;
		}

		int ls=sz(tr[t].l);

		if(pos<=ls){
			tr[t].l=insert_node(tr[t].l,pos,x);
		}else{
			tr[t].r=insert_node(tr[t].r,pos-ls-1,x);
		}
		pull(t);
		return t;
	}

	// pos 番目を削除
	int erase_node(int t,int pos,int& erased){
		int ls=sz(tr[t].l);

		if(pos<ls){
			tr[t].l=erase_node(tr[t].l,pos,erased);
			pull(t);
			return t;
		}

		if(pos>ls){
			tr[t].r=erase_node(tr[t].r,pos-ls-1,erased);
			pull(t);
			return t;
		}

		erased=t;
		return merge(tr[t].l,tr[t].r);
	}

	void recycle(int t){
		tr[t].l=tr[t].r=-1;
		tr[t].sz=1;
		free_id.push_back(t);
	}

	int kth(int k) const{
		int t=root;
		while(1){
			int ls=sz(tr[t].l);
			if(k<ls){
				t=tr[t].l;
			}else if(k==ls){
				return t;
			}else{
				k-=ls+1;
				t=tr[t].r;
			}
		}
	}

	void move_out(int t,vector<T>& v){
		if(t==-1) return;
		move_out(tr[t].l,v);
		v.push_back(move(tr[t].val));
		move_out(tr[t].r,v);
	}

	void move_in(int t,vector<T>& v,int& p){
		if(t==-1) return;
		move_in(tr[t].l,v,p);
		tr[t].val=move(v[p++]);
		move_in(tr[t].r,v,p);
	}

public:

	using value_type=T;
	using reference=T&;
	using const_reference=const T&;
	using size_type=int;
	using difference_type=ptrdiff_t;

	template<bool Const>
	class Iter{
		using Owner=conditional_t<Const,const TreapVector,TreapVector>;

		Owner* owner=nullptr;

		// root -> 現在ノード
		vector<int> path;

		int pos=0;

		void go_left(int t){
			while(t!=-1){
				path.push_back(t);
				t=owner->tr[t].l;
			}
		}

		void go_right(int t){
			while(t!=-1){
				path.push_back(t);
				t=owner->tr[t].r;
			}
		}

		void set_pos(int p){
			pos=p;
			path.clear();

			if(p==owner->size()) return;

			int t=owner->root;
			int k=p;

			while(1){
				path.push_back(t);

				int ls=owner->sz(owner->tr[t].l);

				if(k<ls){
					t=owner->tr[t].l;
				}else if(k==ls){
					return;
				}else{
					k-=ls+1;
					t=owner->tr[t].r;
				}
			}
		}

		Iter(Owner* owner,int pos):owner(owner){
			set_pos(pos);
		}

		friend class TreapVector;
		template<bool> friend class Iter;

	public:
		using iterator_category=bidirectional_iterator_tag;
		using iterator_concept=bidirectional_iterator_tag;
		using value_type=T;
		using difference_type=ptrdiff_t;

		using reference=conditional_t<Const,const T&,T&>;

		using pointer=conditional_t<Const,const T*,T*>;

		Iter()=default;

		template<bool C=Const,enable_if_t<C,int> =0>
		Iter(const Iter<false>& x):owner(x.owner),path(x.path),pos(x.pos){}

		reference operator*() const{
			return owner->tr[path.back()].val;
		}

		pointer operator->() const{
			return &**this;
		}

		Iter& operator++(){
			int cur=path.back();
			if(owner->tr[cur].r!=-1){
				go_left(owner->tr[cur].r);
			}else{
				int child=cur;
				path.pop_back();
				while(!path.empty()&& owner->tr[path.back()].r==child){
					child=path.back();
					path.pop_back();
				}
			}
			++pos;
			return *this;
		}

		Iter operator++(int){
			auto ret=*this;
			++*this;
			return ret;
		}

		Iter& operator--(){
			if(pos==owner->size()){
				go_right(owner->root);
			}else{
				int cur=path.back();
				if(owner->tr[cur].l!=-1){
					go_right(owner->tr[cur].l);
				}else{
					int child=cur;
					path.pop_back();
					while(!path.empty()&& owner->tr[path.back()].l==child){
						child=path.back();
						path.pop_back();
					}
				}
			}
			--pos;
			return *this;
		}

		Iter operator--(int){
			auto ret=*this;
			--*this;
			return ret;
		}

		// begin()+k は使えるが O(log N)
		Iter& operator+=(difference_type d){
			set_pos(pos+(int)d);
			return *this;
		}

		Iter& operator-=(difference_type d){
			return *this+=-d;
		}

		friend Iter operator+(Iter it,difference_type d){
			return it+=d;
		}

		friend Iter operator+(difference_type d,Iter it){
			return it+=d;
		}

		friend Iter operator-(Iter it,difference_type d){
			return it-=d;
		}

		friend difference_type operator-(const Iter& a,const Iter& b){
			return a.pos-b.pos;
		}

		reference operator[](difference_type d) const{
			return *(*this+d);
		}

		friend bool operator==(const Iter& a,const Iter& b){
			return a.owner==b.owner && a.pos==b.pos;
		}

		friend bool operator!=(const Iter& a,const Iter& b){
			return !(a==b);
		}

		friend bool operator<(const Iter& a,const Iter& b){
			return a.pos<b.pos;
		}

		friend bool operator>(const Iter& a,const Iter& b){
			return b<a;
		}

		friend bool operator<=(const Iter& a,const Iter& b){
			return !(b<a);
		}

		friend bool operator>=(const Iter& a,const Iter& b){
			return !(a<b);
		}
	};

	using iterator=Iter<false>;
	using const_iterator=Iter<true>;
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=std::reverse_iterator<const_iterator>;

	TreapVector()=default;

	TreapVector(initializer_list<T> init){
		reserve(init.size());
		for(const auto& x:init){
			push_back(x);
		}
	}

	int size() const{
		return sz(root);
	}

	bool empty() const{
		return root==-1;
	}

	int capacity() const{
		return (int)tr.capacity();
	}

	void reserve(int n){
		tr.reserve(n);
		free_id.reserve(n);
	}

	void clear(){
		tr.clear();
		free_id.clear();
		root=-1;
	}


	T& operator[](int i){
		return tr[kth(i)].val;
	}

	const T& operator[](int i) const{
		return tr[kth(i)].val;
	}

	T& at(int i){
		if(i<0 || i>=size())throw out_of_range("TreapVector::at");
		return (*this)[i];
	}

	const T& at(int i) const{
		if(i<0 || i>=size())throw out_of_range("TreapVector::at");
		return (*this)[i];
	}

	T& front(){
		return (*this)[0];
	}

	const T& front() const{
		return (*this)[0];
	}

	T& back(){
		return (*this)[size()-1];
	}

	const T& back() const{
		return (*this)[size()-1];
	}

	template<class U>
	iterator insert(int pos,U&& val){
		int x=new_node(forward<U>(val));
		root=insert_node(root,pos,x);
		return iterator(this,pos);
	}

	template<class U>
	iterator insert(const_iterator pos,U&& val){
		return insert(pos.pos,forward<U>(val));
	}

	template<class... Args>
	iterator emplace(int pos,Args&&... args){
		return insert(pos,T(forward<Args>(args)...));
	}

	template<class... Args>
	iterator emplace(const_iterator pos,Args&&... args){
		return emplace(pos.pos,forward<Args>(args)...);
	}


	void push_back(const T& x){
		int t=new_node(x);
		root=merge(root,t);
	}

	void push_back(T&& x){
		int t=new_node(move(x));
		root=merge(root,t);
	}

	template<class... Args>
	void emplace_back(Args&&... args){
		push_back(T(forward<Args>(args)...));
	}


	void push_front(const T& x){
		int t=new_node(x);
		root=merge(t,root);
	}

	void push_front(T&& x){
		int t=new_node(move(x));
		root=merge(t,root);
	}

	template<class... Args>
	void emplace_front(Args&&... args){
		push_front(T(forward<Args>(args)...));
	}


	iterator erase(int pos){
		int erased;
		root=erase_node(root,pos,erased);
		recycle(erased);
		return iterator(this,pos);
	}

	iterator erase(const_iterator pos){
		return erase(pos.pos);
	}

	void pop_back(){
		int erased;
		root=erase_node(root,size()-1,erased);
		recycle(erased);
	}

	void pop_front(){
		int erased;
		root=erase_node(root,0,erased);
		recycle(erased);
	}

	iterator begin(){
		return iterator(this,0);
	}

	iterator end(){
		return iterator(this,size());
	}

	const_iterator begin() const{
		return const_iterator(this,0);
	}

	const_iterator end() const{
		return const_iterator(this,size());
	}

	const_iterator cbegin() const{
		return const_iterator(this,0);
	}

	const_iterator cend() const{
		return const_iterator(this,size());
	}


	reverse_iterator rbegin(){
		return reverse_iterator(end());
	}

	reverse_iterator rend(){
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const{
		return const_reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const{
		return const_reverse_iterator(cend());
	}

	const_reverse_iterator crend() const{
		return const_reverse_iterator(cbegin());
	}


	template<class Compare=less<T>>
	void sort(Compare comp=Compare{}){
		vector<T> v;
		v.reserve(size());

		move_out(root,v);

		sort(v.begin(),v.end(),comp);

		int p=0;
		move_in(root,v,p);
	}

	template<class Compare=less<T>>
	void revsort(Compare comp=Compare{}){
		vector<T> v;
		v.reserve(size());

		move_out(root,v);

		sort(v.begin(),v.end(),[&](const T& a,const T& b){return comp(b,a);});

		int p=0;
		move_in(root,v,p);
	}
};

int main(){
    ll n;
    cin>>n;
	TreapVector<ll> v;
	while(n--){
		ll t;
		cin>>t;
		if(t==1){
			ll x;
			cin>>x;
			v.insert(v.end(),x);
		}else if(t==2){
			ll x,k;
			cin>>x>>k;
			k--;
			v.insert(v.begin()+k,x);
		}else{
			cout<<v[0]<<endl;
			auto it=v.begin();
			it++;
			it--;
			v.erase(it);
		}
	}
}