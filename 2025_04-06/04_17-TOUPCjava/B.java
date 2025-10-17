import java.util.*;

public class B {
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);
        int d=scan.nextInt();
		int a=scan.nextInt();
		int y=scan.nextInt();
		if(d<=a&&y<d){
			System.out.println("Winner");
		}else if(d<=y&&a<d){
			System.out.println("Loser");
		}else{
			System.out.println("Draw");
		}
		scan.close();
    }
}
