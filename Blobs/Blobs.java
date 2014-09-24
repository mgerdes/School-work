import java.util.*;

public class Blobs {

	static final int WIDTH = 10;
	static final int HEIGHT = 10;

	static boolean isBlob[][] = new boolean[HEIGHT][WIDTH];
	static boolean visited[][] = new boolean[HEIGHT][WIDTH];

	static int numberOfBlobs = 0;

	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);			

		createBlobs(10);
		dfs();
		printBlobs();
		System.out.println(numberOfBlobs);

	}

	public static void createBlobs(int percentage) {
		for (int row = 0; row < HEIGHT; row++) {
			for (int col = 0; col < WIDTH; col++) {
				if (Math.random() < percentage / 100.0) {
					isBlob[row][col] = true;
				} else {
					isBlob[row][col] = false;
				}
			}
		}	
	}
	
	public static void printBlobs() {
		System.out.println();
		for (int row = 0; row < HEIGHT; row++) {
			for (int col = 0; col < WIDTH; col++) {
				System.out.print(isBlob[row][col] ? "X" : "-");
			}
			System.out.println();
		}
	}

	public static void dfs() {
		for (int row = 0; row < HEIGHT; row++) {
			for (int col = 0; col < WIDTH; col++) {
				if (!visited[row][col] && isBlob[row][col]) {
					dfsVisit(row, col);
					numberOfBlobs++;
				}
			}
		}
	}

	public static void dfsVisit(int row, int col) {
		visited[row][col] = true;

		System.out.printf("visited %d, %d\n", row, col);

		int rowOffsets[] = {-1,0,1,0,1,1,-1,-1};
		int colOffsets[] = {0,-1,0,1,1,-1,1,-1};

		for (int i = 0; i < 8; i++) {
			int curRow = row + rowOffsets[i];
			int curCol = col + colOffsets[i];
			if (curRow < HEIGHT && curCol < WIDTH && curRow > -1 && curCol > -1) {
				if (!visited[curRow][curCol] && isBlob[curRow][curCol]) {
					dfsVisit(curRow, curCol);
				}
			}
		}
	}

}
