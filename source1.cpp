#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
	//가로세로높이 & 바뀐가로세로높이(개수)
	int row, col, height;
	int new_row, new_col, new_height;

	//row, col, height의 끝 좌표(0~), 남은 칸(복셀) 개수
	//시작(row,col,height_start)는 0
	int row_last, row_remain;
	int col_last, col_remain;
	int height_last, height_remain;

	//새로운 row, col, height 시작 좌표, 임시끝 좌표, 이동된 끝 좌표
	int new_row_start, new_row_tempLast, new_row_last;
	int new_col_start, new_col_tempLast, new_col_last;
	int new_height_start, new_height_tempLast, new_height_last;

	int step_size;	//해상도 축소 파라미터

	//밀도값 저장 배열
	double*** M_default = NULL;
	double*** M_new = NULL;


	double init_data[7];	//row, col, height 저장용

	//0204
	//0840
	//1003
	//1059
	//1303
	//1709
	//1815
	//4372
	//5805
	//6493
	//10676

	char S[40] = "10676";
	char S1[40] = "emd_";
	strcat(S1, S);						//S1 = "emd_****"
	char sit[40] = ".sit";				//sit = ".sit"
	strcat(S1, sit);					// S1 = "emd_****.sit"


	FILE* fp1 = fopen(S1, "r");			// S1 = "emd_****.sit"
	//FILE* fp3 = fopen("2step_emd_0204.sit", "w");
	
	
	//FILE *fp2 = fopen("emd_1003_density.sit", "w");
	//FILE *fp4 = fopen("2step_emd_1003_coordinate.sit", "w");


	//test용
	/*
	FILE *fp1 = fopen("emd_test.sit", "r");
	//FILE *fp2 = fopen("emd_test_density.sit", "w");
	FILE *fp3 = fopen("new_emd_test.sit", "w");
	FILE *fp4 = fopen("new_emd_test_coordinate.sit", "w");
	*/

	if (fp1 == NULL)
	{
		printf("open() error!");
		exit(1);
	}

	//row,col,height 설정
	for (int i = 0; i < 7; i++)
	{
		fscanf(fp1, "%lf", &init_data[i]);
		if (i == 4)
			row = (int)init_data[i];
		else if (i == 5)
			col = (int)init_data[i];
		else if (i == 6)
			height = (int)init_data[i];
	}

	//기본 배열 동적할당
	M_default = new double** [row];
	for (int i = 0; i < row; i++)
	{
		M_default[i] = new double* [col];
		for (int j = 0; j < col; j++)
			M_default[i][j] = new double[height];
	}

	//밀도값 불러오기
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			for (int k = 0; k < height; k++) {
				fscanf(fp1, "%lf", &M_default[i][j][k]);
				//fprintf(fp2, "%lf\n", M_default[i][j][k]);
			}
		}
	}

	//row_last = row_start + row -1 = 0 + row -1
	row_last = row - 1;
	col_last = col - 1;
	height_last = height - 1;

	//step_size 입력받기
	cout << "row , col , height = " << row << " , " << col << " , " << height << endl;
	cout << "step_size 입력: ";
	cin >> step_size;
	cout << "해상도를 " << step_size << "만큼씩 나누어 낮춥니다." << endl;

	//파일 출력
	char stepSize[40] = "";				//stepsize step숫자
	char stepSit[40] = "";				//step적용 sit 파일 이름
	char stepName[40] = "step_";		//stepName = "step_"
	sprintf(stepSize, "%d", step_size); //stepSize = "n"
	strcat(stepSize, stepName);			//stepSize = "nstep_"
	strcat(stepSit, stepSize);			//stepSit = "nstep_"
	strcat(stepSit, S1);				//stepSit = "nstep_emd_****.sit"

	//FILE* fp3 = fopen("2step_emd_0204.sit", "w");
	FILE* fp3 = fopen(stepSit, "w");


	//new_row 계산
	new_row = (row - 1) / step_size + 1;
	new_col = (col - 1) / step_size + 1;
	new_height = (height - 1) / step_size + 1;

	//시작점이 0인(옮기지않은) 임시 last 좌표 계산
	new_row_tempLast = (new_row - 1) * step_size;
	new_col_tempLast = (new_col - 1) * step_size;
	new_height_tempLast = (new_height - 1) * step_size;

	//남는 칸 개수(remain) 값 구하기
	row_remain = row_last - new_row_tempLast;
	col_remain = col_last - new_col_tempLast;
	height_remain = height_last - new_height_tempLast;

	//남는 칸 개수의 2분1의 만큼을 앞에서 땅겨서 start
	new_row_start = row_remain / 2;
	new_col_start = height_remain / 2;
	new_height_start = height_remain / 2;

	//시작점이 바뀐 last 좌표 계산
	new_row_last = new_row_tempLast + new_row_start;
	new_col_last = new_col_tempLast + new_col_start;
	new_height_last = new_height_tempLast + new_height_start;

	//디버깅용
	cout << "new_row : " << new_row << endl;
	cout << "new_row_tempLast : " << new_row_tempLast << endl;
	cout << "row_remain : " << row_remain << endl;
	cout << "new_row_start : " << new_row_start << endl;
	cout << "new_row_last : " << new_row_last << endl;


	//새 배열 동적할당
	M_new = new double** [new_row];
	for (int i = 0; i < new_row; i++)
	{
		M_new[i] = new double* [new_col];
		for (int j = 0; j < new_col; j++)
			M_new[i][j] = new double[new_height];
	}

	//원본 sit와 같은 형식 유지
	for (int i = 0; i < 4; i++)
		fprintf(fp3, "0 ");
	fprintf(fp3, "%d ", new_row);
	fprintf(fp3, "%d ", new_col);
	fprintf(fp3, "%d\n\n", new_height);


	for (int c = 0; c < new_row; c++) {
		for (int s = 0; s < new_col; s++) {
			for (int t = 0; t < new_height; t++)
			{
				M_new[c][s][t] = M_default[new_row_start + c * step_size][new_col_start + s * step_size][new_height_start + t * step_size];
				fprintf(fp3, "%lf ", M_new[c][s][t]);
				//fprintf(fp4, "[%d][%d][%d] ", new_row_start + c * step_size, new_col_start + s * step_size, new_height_start + t * step_size);
			}
			//fprintf(fp4, "\n");
		}
	}

	//동적할당 해제
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			delete[] M_default[i][j];
		delete[] M_default[i];
	}
	delete[] M_default;

	for (int i = 0; i < new_row; i++)
	{
		for (int j = 0; j < new_col; j++)
			delete[] M_new[i][j];
		delete[] M_new[i];
	}
	delete[] M_new;

	//파일 닫기
	fclose(fp1);
	///fclose(fp2);
	fclose(fp3);
	//fclose(fp4);

	return 0;

}
