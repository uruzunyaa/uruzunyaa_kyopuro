import java.util.Scanner;

public class Main {
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int n=scan.nextInt();
		String s = scan.next();
		String t = "";
		for(int i=0;i<n;i++){
			t.append("遵義力行");
		}
		if(s.equals(t))System.out.println("Yes");
		else System.out.println("No");
	}
	
}
