#include <iostream>
#include <iomanip>
#include <string>
#include "Tree.h"

void SetTable( const float p[], const float q[], float w[][8], float c[][8], int r[][8] );

template<typename T>
void ShowTable( const T table[][8], const std::string name );

int main()
{
	float p[8] = { NULL, 0.1f, 0.07f, 0.06f, 0.05f, 0.05f, 0.04f, 0.03f };
	float q[8] = { 0.1f, 0.12f,0.07f, 0.06f, 0.06f, 0.05f, 0.08f, 0.06f };
	float w[8][8] = { 0.0f }; // weight
	float c[8][8] = { 0.0f }; // cost
	int r[8][8] = { 0 };      // root
	Tree obst;                // result obst

	SetTable( p, q, w, c, r );
	ShowTable<float>( w, "Weight Table" );
	ShowTable<float>( c, "Cost Table" );
	ShowTable<int>( r, "Root Table" );

	obst.SetRoot( obst.Make( r, 0, 7 ) ); // 루트 테이블로 OBST 만들고 root 노드 설정
	std::cout << "--------------------Print tree by preorder--------------------" << std::endl << std::endl;
	obst.Preorder( obst.GetRoot() ); // 전위 순회로 트리 출력
}

void SetTable( const float p[], const float q[], float w[][8], float c[][8], int r[][8] )
{

	for( int i = 0; i < 8; ++i )
	{
		w[i][i] = q[i];
	}
	for( int x = 1; x < 8; ++x )
	{
		for( int i = 0; i < 8 - x; ++i )
		{
			/*
				<COST 테이블 값을 구하는 아래의 공식을 그대로 구현>
				c[i,j] = min( i < k <= j ) { c[i, k-1] + c[k, j] } + w[i, j]
			*/
			int j = i + x;
			// k = i + 1 일 때
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			c[i][j] = c[i][i] + c[i + 1][j]; // i < k <= j
			r[i][j] = i + 1;
			// k = i + 2 부터 j 까지 반복하면서 최소값 찾기
			// 최소 COST 값을 만드는 k 값을 루트 테이블에 넣어줌.
			for( int k = i + 2; k <= j; ++k )
			{
				if( c[i][j] > ( c[i][k - 1] + c[k][j] ) )
				{
					c[i][j] = c[i][k - 1] + c[k][j];
					r[i][j] = k;
				}
			}
			// WEIGHT 값도 더하여 해당 위치의 최종 COST 값 할당.
			c[i][j] = c[i][j] + w[i][j];
		}
	}
}

template<typename T>
void ShowTable( const T table[][8], const std::string name )
{
	std::cout << "--------------------Table--------------------" << std::endl << std::endl;

	std::cout << "< " << name << " >" << std::endl << std::endl;
	std::cout << std::setw( 5 ) << std::left << ' ';
	for( int i = 0; i < 8; ++i )
	{
		std::cout << std::setw( 5 ) << std::left << i;
	}
	std::cout << std::endl;
	for( int i = 0; i < 8; ++i )
	{
		std::cout << std::setw( 5 ) << std::left << i;
		for( int j = 0; j < 8; ++j )
		{
			std::cout << std::setw( 5 ) << std::left << table[i][j];
		}
		std::cout << std::endl;
	}
}
