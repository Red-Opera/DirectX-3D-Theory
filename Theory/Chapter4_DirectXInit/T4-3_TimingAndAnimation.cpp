#include "stdafx.h"

// ========================================================
//	Device 생성
// ========================================================

/*
	- 정밀한 시간 측정을 위해서 Windows가 성능 타이머(Performance Timer)를 사용한다.
	- 이러한 성능 타이머를 성능 카운터(Performance Counter)라고 한다.

	QueryPerformanceCount
		- 성능 타이머는 시간을 개수(Count)단위로 측정한다.
		- 현재 시간을 측정하기 위해서는 QueryPerformanceCount 함수를 사용하면 된다.
		- QueryPerformanceCount는 입력한 매개변수를 반환하며 반환 형은 64비트 정수이다.

	QueryPerformanceFrequency
		- 초당 개수를 얻기 위해서는 QueryPerformanceFrequency 함수를 사용하면 된다.
		- QueryperformanceFrequency도 QueryPerformanceCount와 같은 방식으로 작동한다.
		- QueryperformanceFrequency의 값을 역수로 취하면 프레임을 얻을 수 있다.
		- 역수 취한 값에 QueryPerformanceCount을 곱하면 해당 값을 초 단위로 나타낼 수 있다.

	- 어떤 작업의 걸린 시간을 측정하기 위해서는 QueryPerformanceCount간의 값을 뻬면 된다.
*/

// ========================================================
//	프레임 간 경과 시간
// ========================================================

/*
	- 프레임 간 경과시간은 i번째 프레임과 i-1프레임에서의 성능 타임 값 (Δt = t(i) - t(i - 1))
	- 자연스러운 애니메이션을 위해서 적어도 30은 넘어야 한다.
*/

// ========================================================
//	전체 시간
// ========================================================

/*
	- 응용 프로그램이 시작된 이후에 흐른 시간을 전체 시간(Total Time)이리고 한다.
	- 전체 시간을 구하는 방법은 레벨 시작 후 그때 시간과 현재 시간을 빼면 구할 수 있다.

	- 전체 시간을 이용하는 다른 용도는 애니메이션의 갱신하기 위해서이다.
	- 일지 정지한 시간을 제외한 시간을 구하기 위해서는 전체 시간에서 일시정지한 시간을 빼야 한다.
*/