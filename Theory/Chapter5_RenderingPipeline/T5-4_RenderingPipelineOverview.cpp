#include "stdafx.h"

// ========================================================
//	렌더링 파이프라인의 개요
// ========================================================

/*
	- 가상 카메라가 3차원 장면의 모습을 2차원 이미지를 생성하는데 필요한 일련의 단계(Stage)

	렌더링 파이프라인 단계
		1. 입력 조립기(IA)
		2. 정점 셰이더(VS)
		3. 덮개 셰이더(HS)
		4. 테셀레이터
		5. 기하 셰이더(GS)
		6. 스트림 출력(SO)
		7. 레스터화기
		8. 픽셀 셰이더(PS)
		9. 출력 병합기(OS)
*/