import java.util.*;

public class C{
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);
		String a=scan.next();
		String b=scan.next();
		int n=scan.nextInt();
		String [] s=new String[n];

		int ai=0,bi=0;
		for(int i=0;i<n;i++){
			s[i]=scan.next();
			if(a.equals(s[i]))ai=i;
			if(b.equals(s[i]))bi=i;
		}
		System.out.println(Math.abs(ai-bi)-1);
		scan.close();
    }
}
