import java.util.*;
public class Main {
	static Scanner scan = new Scanner(System.in);

    // １回の入力につき、１回のsolve関数を使う
    public static int solve() {
		int n=scan.nextInt();
		
        if (n==0)return 1;
		int [] a = new int[n];
		
		int ans=0;
		for(int i=0;i<n;i++){
			a[i]=scan.nextInt();
			if(Math.abs(a[ans]-2023)>Math.abs(a[i]-2023))ans=i;
		}

		System.out.println(ans+1);
        return 0;
    }

    public static void main(String[] args){
        while (solve()==0);
    }
}

