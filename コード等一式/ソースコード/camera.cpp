#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "scene.h"

void Camera::Init()
{
	m_position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_target2 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Box* box = scene->GetGameObject<Box>();

	m_target = player->GetPosition();
	m_target.y += 7.0f; // �^�[�Q�b�g�̍�������

	// ���͂ɂ��J�����̉�]�X�V
	if (Input::GetKeyPress('J')) m_rotation.y -= 0.05f;
	if (Input::GetKeyPress('L')) m_rotation.y += 0.05f;

	// �p�x�̃��b�v���� (0 ~ 2��)
	if (m_rotation.y < 0.0f) m_rotation.y += XM_2PI;
	if (m_rotation.y > XM_2PI) m_rotation.y -= XM_2PI;

	// ��{�̃J��������
	XMFLOAT3 baseDistance;
	baseDistance.x = 15.0f;
	baseDistance.y = 15.0f;
	baseDistance.z = 15.0f;


	// �v���C���[��Box�̋������v�Z
	XMFLOAT3 boxPos = box->GetPosition();
	XMFLOAT3 boxScale = box->GetScale();
	XMFLOAT3 playerPos = player->GetPosition();
	XMFLOAT3 adjustedDistance;

	float dx = playerPos.x - boxPos.x;
	float dy = playerPos.y - boxPos.y;
	float dz = playerPos.z - boxPos.z;

	float playerBoxDistance;
	playerBoxDistance = sqrtf(dx * dx + dy * dy + dz * dz);

	// Box�̔��a�i�܂��͋��e�����j��ݒ�iBox�̑傫���ɍ��킹�Ē����j
	const float boxRadius = 30.0f;

	// �v���C���[��Box�ɋ߂Â����ꍇ�A�����ɉ����ăJ�����������k�߂�
	adjustedDistance = baseDistance;

	if (playerBoxDistance < boxScale.x * 550 + 5.0f && 
		playerBoxDistance < boxScale.z * 600 + 5.0f) // 5.0f�͗]�T�̋���
	{
		// Box�ɋ߂Â��قǃJ�����������k�߂�i�ő�5m�k�߂�j
		float shrinkAmountX = (boxRadius - playerBoxDistance);
		float shrinkAmountY = (boxRadius - playerBoxDistance);
		float shrinkAmountZ = (boxRadius - playerBoxDistance);
		if (shrinkAmountX > 5.0f && 
			shrinkAmountZ > 5.0f && 
			shrinkAmountY > 5.0f)
		{
			shrinkAmountX = 5.0f;
			shrinkAmountY = 5.0f;
			shrinkAmountZ = 5.0f;
		}

		adjustedDistance.x = baseDistance.x - shrinkAmountX;
		adjustedDistance.y = baseDistance.y - shrinkAmountY;
		adjustedDistance.z = baseDistance.z - shrinkAmountZ;
		if (adjustedDistance.x < 5.0f && 
			adjustedDistance.y < 5.0f && 
			adjustedDistance.z < 5.0f)
		{
			adjustedDistance.x = 5.0f; 
			adjustedDistance.y = 5.0f; 
			adjustedDistance.z = 5.0f; 
		}
	}

	// �J�����̗��z�ʒu���v�Z�i�v���C���[����̋����𒲐��ς݁j
	m_position.x = m_target.x + adjustedDistance.x * sinf(m_rotation.y);
	m_position.y = m_target.y + 2.0; // �����͌Œ�
	m_position.z = m_target.z + adjustedDistance.z * cosf(m_rotation.y);

	// Box�ƃJ�����̏Փ˔���i�P���ȋ��������OK�j
	float dx_cam = m_position.x - boxPos.x;
	float dy_cam = m_position.y - boxPos.y;
	float dz_cam = m_position.z - boxPos.z;

	XMFLOAT3 camBoxDistance ;
	camBoxDistance.x = sqrtf(dx_cam * dx_cam);
	camBoxDistance.y = sqrtf(dy_cam * dy_cam);
	camBoxDistance.z = sqrtf(dz_cam * dz_cam);

	if (camBoxDistance.z < boxScale.z * 580)
	//if(camBoxDistance < boxRadius)
	{
		// �J������Box�ɓ����Ă��܂�����A�J�����ʒu��Box�̊O�ɉ����o��
		// �J�����ʒu��Box���S����O���Ɉړ�
		float overlap;
		overlap = boxRadius - camBoxDistance.z;

		// ���K���x�N�g��
		float nx = dx_cam / camBoxDistance.x;
		float ny = dy_cam / camBoxDistance.y;
		float nz = dz_cam / camBoxDistance.z;

		m_position.x += nx * overlap;
		m_position.y += ny * overlap;
		m_position.z += nz * overlap;

	}
}


void Camera::Draw()
{
	XMFLOAT3 up{ 0.0f, 5.0f, 0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&up));//�ǂ��ɂ����Ăǂ��Ɍ������邩

	Renderer::SetViewMatrix(viewMatrix);

	
	XMStoreFloat4x4(&m_ViewMatrix,viewMatrix);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	XMMATRIX projectionmatrix;
	projectionmatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projectionmatrix);

	////�J�����E�B���h�E
	//ImGui::Begin("Camera");

	//ImGui::InputFloat("Position", (float*)&m_position);
	//static float col1[3] = { 1.0f, 0.0f, 0.2f };
	//static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
	//ImGui::ColorEdit3("color 1", col1);

	//ImGui::End();
}


