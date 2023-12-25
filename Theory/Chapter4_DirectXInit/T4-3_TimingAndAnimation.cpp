#include "stdafx.h"

// ========================================================
//	Device ����
// ========================================================

/*
	- ������ �ð� ������ ���ؼ� Windows�� ���� Ÿ�̸�(Performance Timer)�� ����Ѵ�.
	- �̷��� ���� Ÿ�̸Ӹ� ���� ī����(Performance Counter)��� �Ѵ�.

	QueryPerformanceCount
		- ���� Ÿ�̸Ӵ� �ð��� ����(Count)������ �����Ѵ�.
		- ���� �ð��� �����ϱ� ���ؼ��� QueryPerformanceCount �Լ��� ����ϸ� �ȴ�.
		- QueryPerformanceCount�� �Է��� �Ű������� ��ȯ�ϸ� ��ȯ ���� 64��Ʈ �����̴�.

	QueryPerformanceFrequency
		- �ʴ� ������ ��� ���ؼ��� QueryPerformanceFrequency �Լ��� ����ϸ� �ȴ�.
		- QueryperformanceFrequency�� QueryPerformanceCount�� ���� ������� �۵��Ѵ�.
		- QueryperformanceFrequency�� ���� ������ ���ϸ� �������� ���� �� �ִ�.
		- ���� ���� ���� QueryPerformanceCount�� ���ϸ� �ش� ���� �� ������ ��Ÿ�� �� �ִ�.

	- � �۾��� �ɸ� �ð��� �����ϱ� ���ؼ��� QueryPerformanceCount���� ���� ���� �ȴ�.
*/

// ========================================================
//	������ �� ��� �ð�
// ========================================================

/*
	- ������ �� ����ð��� i��° �����Ӱ� i-1�����ӿ����� ���� Ÿ�� �� (��t = t(i) - t(i - 1))
	- �ڿ������� �ִϸ��̼��� ���ؼ� ��� 30�� �Ѿ�� �Ѵ�.
*/

// ========================================================
//	��ü �ð�
// ========================================================

/*
	- ���� ���α׷��� ���۵� ���Ŀ� �帥 �ð��� ��ü �ð�(Total Time)�̸��� �Ѵ�.
	- ��ü �ð��� ���ϴ� ����� ���� ���� �� �׶� �ð��� ���� �ð��� ���� ���� �� �ִ�.

	- ��ü �ð��� �̿��ϴ� �ٸ� �뵵�� �ִϸ��̼��� �����ϱ� ���ؼ��̴�.
	- ���� ������ �ð��� ������ �ð��� ���ϱ� ���ؼ��� ��ü �ð����� �Ͻ������� �ð��� ���� �Ѵ�.
*/