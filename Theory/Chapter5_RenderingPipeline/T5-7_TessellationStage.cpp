#include "stdafx.h"

// ========================================================
//	�׼����̼� �ܰ� (Tessellation)
// ========================================================

/*
	- ���� ���̴�(HS)�ܰ� ���� �̷������ �ܰ�
	- �ﰢ���� �� �߰� �ɰ��� ���ο� �ﰢ���� ����� �ܰ�
	- ����� �ﰢ���� �׼����̼��� �����Ͽ� ������Ʈ�� ���������� ǥ���ϰ� �ָ��ִ� ������Ʈ�� �׼����̼��� �������� �ʴ� ���μ���(Level-Of-Detail, LOD)�� ������ �� �ִ�.
	- �޸𸮿��� LowPoly�� ��Ƶ״ٰ� �ﰢ���� ����� �� �ﰢ���� �߰��ϴ� ������� ó��
	- �ִϸ��̼��̳� ������ �ش� �޽ÿ� ���� ó���� �ϰ� �׼����̼��� ������ �� HighPoly�� �������� ó���Ͽ� ��귮�� ����
	- �׼����̼� �ܰ�� CPU���� �ﰢ���� ���� ������ ó���� �� GPU�� �ٽ� ������ �� �������� �Ѵ�.
	- �׼����̼� �ܰ�� CPU�� �δ��� �ִ� �����̱� ������ DirectX 3D���� ���� ��ġ�� �����ϵ��� �ϴ� API�� �����Ѵ�.
	- �׼����̼��� ������ �����ϴ�.
*/