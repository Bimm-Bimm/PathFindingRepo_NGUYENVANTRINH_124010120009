#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 19
#define MAX_COLUMN 19
#define MAX 19

typedef struct POINT
{
  int row, column ,value;
  bool visited;
  struct POINT* prev;

} point_t;

point_t matrix[MAX_ROW][MAX_COLUMN] = {0};

typedef struct {
  point_t data[MAX];  // lưu trữ các nút
  int front;          // chỉ số đầu của hàng đợi
  int rear;         // chỉ số cuối của hàng đợi

}Queue;

//hàm khởi tạo queue
void initQueue(Queue *q) {
  q->front = 0;
  q->rear = -1;
}

//hàm checkQueue có rỗng không
int isEmpty(Queue q) {
  return (q.rear < q.front);
}

//hàm check queue đầy chưa
int isFull(Queue q) {
  if((q.rear - q.front) == MAX - 1) {
    return 1;
  }
  else {
    return 0;
  }
}

//thêm vào queue
void enQueue(Queue *q, point_t x) {
  if (!isFull(*q)) {
        if(q->rear == MAX - 1) {
        for(int i = q->front; i <= q->rear; i++){
        q->data[i - q->front] = q->data[i];
      }
      q->rear = MAX - q->front - 1;
      q->front = 0;
    }
    q->rear = q->rear + 1;
    q->data[q->rear] = x;
  }
}

//lấy ra từ queue
point_t deQueue(Queue *q) {
  point_t d;   
  if (!isEmpty(*q)) {
    d = q->data[q->front];
    q->front = q->front +1;
    }
  if (q->front > q->rear) {
    initQueue(q);
  }
  return d;
}

//kiểm tra tọa độ
bool checkCoordinate(int dong, int cot) {
  bool ret = false;
  if ((0 <= dong && dong < MAX_ROW ) && (0 <= cot && cot < MAX_ROW)) {
    ret = true;
  }
  return ret;
}

//tìm các điểm xung quanh
void findSurroundingPoint(int dong, int cot, point_t surroundingPnt[4], int* count){
  // khởi tạo số biến đếm số lượng các nút có thể đi được quanh 1 vị trí
  int tempCnt = 0;
  // kiểm tra xem vị trí điểm bên phải có đến được không?
  if ((checkCoordinate(dong, cot+1) == true) && (matrix[dong][cot+1].value == 1)){                   
    surroundingPnt[tempCnt ] = matrix[dong][cot+1];
    tempCnt++;
  }
  // kiểm tra xem vị trí điểm bên dưới có đến được không?
  if ((checkCoordinate(dong+1, cot) == true) && (matrix[dong+1][cot].value == 1)) {                  
    surroundingPnt[tempCnt ] = matrix[dong+1][cot];
    tempCnt++;
  }
  // kiểm tra xem vị trí điểm bên trái có đến được không?
  if ((checkCoordinate(dong, cot-1) == true) && (matrix[dong][cot-1].value == 1)) {
    surroundingPnt[tempCnt ] = matrix[dong][cot-1];
    tempCnt++;
  }
  // kiểm tra xem vị trí điểm bên trên có đến được không?
  if ((checkCoordinate(dong-1, cot) == true) && (matrix[dong-1][cot].value == 1)) {                    
    surroundingPnt[tempCnt ] = matrix[dong-1][cot];
    tempCnt++;
    }
  *count = tempCnt;
}

//tìm đường đi ngắn nhất
void findShortestPath (int dong, int cot){
  point_t* temp;
  Queue q;
  initQueue(&q);
  matrix[7][9].visited = true;
  enQueue(&q, matrix[7][9]);
  bool found = false;
  while (!isEmpty(q) && !found){
    int count = 0;
    point_t pp[4] = {0};
    point_t p = deQueue(&q);
    findSurroundingPoint(p.row, p.column, &pp[0], &count);
    for (int i = 0; i < count ; i++){
      if (!matrix[pp[i].row][pp[i].column].visited){
        matrix[pp[i].row][pp[i].column].visited = true;
        matrix[pp[i].row][pp[i].column].prev = &matrix[p.row][p.column];
        if (pp[i].row == dong && pp[i].column == cot){
          found = true;
          temp = &matrix[pp[i].row][pp[i].column];
          break;
        }
        else{
          enQueue(&q, matrix[pp[i].row][pp[i].column]);
        }
      }
    }
  }
  if (found == true){ 
        printf("duong di ngan nhat den A(%d, %d) la:\n", dong, cot);
        while (temp->prev != NULL){
          printf ("(%d, %d) -> ", temp->row, temp->column);
          temp = temp->prev;
        }
        printf("(%d, %d)", temp->row, temp->column);
    }
  else{
    printf("khong co duong toi A");
  }
}

int main(){
  // khởi tạo mảng matrix
  int dau_vao[MAX_ROW][MAX_COLUMN] = {
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//1
    ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}//2
    ,{0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0}//3
    ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}//4
    ,{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0}//5
    ,{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0}//6
    ,{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}//7
    ,{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0}//8
    ,{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}//9
    ,{0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0}//10  
    ,{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}//11
    ,{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0}//12
    ,{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}//13
    ,{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0}//14
    ,{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0}//15
    ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}//16
    ,{0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0}//17
    ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}//18
    ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//19
  };
  for (int i = 0; i < MAX_ROW; i++){
    for (int j = 0; j < MAX_ROW; j++){
      matrix[i][j].row = i;
      matrix[i][j].column = j;
      matrix[i][j].value = dau_vao[i][j];
      printf("%c ",(matrix[i][j].value == 0)? '#' : (i == 7 && j == 9)? 'e' : ' ');
    }
    printf("\n");
  }
  printf("ban la e day!\n");
  
  int x = 0; int y = 0;
  //yêu cầu người dùng nhập tọa độ điểm
  do{
  printf("nhap toa do diem can toi\n");
  scanf("%d%d", &y, &x);
  } while (x < 0 || y < 0 || x >= MAX_ROW || y >= MAX_ROW || dau_vao[y][x] != 1);

  //chạy hàm tìm đường đi ngắn nhất
  findShortestPath(y,x);
  return 0;
}