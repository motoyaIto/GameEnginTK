//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>

#include "DebugCamera.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:
	using Matrix = DirectX::SimpleMath::Matrix;

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
	
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//�f�o�b�N�p
	std::unique_ptr<DebugCamera> m_debugCamera;

	//�G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> m_factory;

	//�n�ʃ��f��
	std::unique_ptr<DirectX::Model> m_modelGround;

	//�e�B�[�|�b�g���f��
	/*std::unique_ptr<DirectX::Model> m_teapot;
	DirectX::SimpleMath::Matrix m_worldTeapot[20];
	Matrix m_transmat[20];
	int m_ro;*/

	//��
	std::unique_ptr<DirectX::Model> m_hed;

	//�n�ʃ��[���h�s��
	//DirectX::SimpleMath::Matrix m_worldGround[100 * 100];

	////�V�����f��
	std::unique_ptr<DirectX::Model> m_modelSkydorme;


	////�������f��
	//std::unique_ptr<DirectX::Model> m_hemisphere;

	////�������[���h�s��
	//int m_worldHemisphereNam;
	//DirectX::SimpleMath::Matrix m_worldHemisphere[20];

	//�X�P�[��
	//Matrix scalemat[20];
	//��]�s��
	//���[��
	//Matrix rotmatZ[20];
	//�r�b�`()
	//Matrix rotmatX[20];
	//���[(���ʊp)
	//Matrix rotmatY[20];
	//��]�s��̌v�Z
	//Matrix rotmat[20];
	//���s�ړ�
	//Matrix transmat[20];
	//���
	//float m_mawaru;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//���@�̍��W
	DirectX::SimpleMath::Vector3 tank_pos;
	//���@�̉�]
	float tank_angl;
	//���@�̃��[���h�s��
	Matrix tank_world;
};