import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);

		while(true){
			int n = scan.nextInt();
			if(n==0)break;

			int[] a = new int[n];
			for(int i = 0;i<n;i++){
				a[i]= scan.nextInt();
			}

			Arrays.sort(a);

			int ans=0;
			for(int i = 0;i<n;i++){
				for(int j = 0;j<=i;j++){
					//jから始まって、iで終わる区間が条件か満たすか判定
					boolean f=true;
					for(int k=j;k<i;k++){
						if(a[k]+1!=a[k+1])f=false;
					}
					if(f){
						ans=Math.max(i-j+1,ans);
					}
				}
			}
			System.out.println(ans);
		}
		
		scan.close();
    }
}
