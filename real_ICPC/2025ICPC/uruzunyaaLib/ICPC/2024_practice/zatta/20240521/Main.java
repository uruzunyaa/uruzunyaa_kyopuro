import java.util.*;
public class Main {
	static Scanner sc = new Scanner(System.in);

    // solve関数の定義
    public static int solve() {
		int n=sc.nextInt();

        //nが0なので終了する。
        if (n==0)return 1;

		int [] a=new int[n];

		for(int i=0;i<n;i++){
			a[i]=sc.nextInt();
		}
		Arrays.sort(a);
		
		int mn=1000000000;
		for(int i=0;i<n-1;i++){
			mn=Math.min(a[i+1]-a[i],mn);
		}
		System.out.println(mn);
        
        return 0;
    }

    public static void main(String[] args){
        while (true){
            if (solve() == 1){
                break;
            }
        }
    }
}
