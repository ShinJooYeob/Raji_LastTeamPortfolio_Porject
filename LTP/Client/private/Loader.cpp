#include "stdafx.h"
#include "..\Public\Loader.h"



//////////////////////////////////////////////////////////////////////////

///??/////////////////////////////////////////////////////////////////////
#include "StaticInstanceMapObject.h"
#include "TestObject.h"
#include "AnimationClip.h"
#include "Navigation.h"
#include "TestStaticObject.h"

//////////////////////////////////////////////////////////////////////////

////STA0GE_4//////////////////////////////////////////////////////////////////
//Boss
#include "Rangda.h"
#include "Chiedtian.h"
#include "Snake.h"
#include "Mahabalasura.h"

//Weapons
#include "Chiedtuan_Weapon.h"
#include "Chiedtuan_2Page_Weapon.h"
#include "Rangda_Finger.h"
#include "Rangda_Statue.h"
#include "Randa_Wasp_Bullet.h"
#include "Mahabalasura_Arms.h"
#include "Mahabalasura_AttackArms.h"
#include "Mahabalasura_Weapon.h"
#include "CopyMahabalasura.h"
#include "Mahabalasura_SpearWave.h"
#include "Mahabalasura_AttackSpear.h"
#include "Snake_Poison_Raser.h"
#include "Volcano.h"
#include "CflameTerrain.h"

//Static_Map
#include "Demon_Tree.h"
#include "TreeMesh.h"
#include "MandalaPuzzle.h"
#include "MandalaMesh.h"
#include "Gear_Puzzle.h"
#include "Gear.h"

//UI
#include "SkillUI.h"
#include "LobbyUI.h"
#include "PauseUI.h"
#include "GraphicUI.h"
#include "SoundUI.h"
#include "IngameUI.h"
#include "TaikoUI.h"


//ParticleCollider
#include "ParticleCollider.h"
#include "Particle_ColliderInOut.h"

//Dynamic_Map
#include "FemaleStatue.h"

//TestEffect
#include "Rangda_MagicCircle.h"
//////////////////////////////////////////////////////////////////////////////

////Jino_Jino//////////////////////////////////////////////////////////////////
// Player
#include "Player.h"
#include "Golu.h"
// Player_Weapon
#include "PlayerWeapon_Spear.h"
#include "PlayerWeapon_Bow.h"
#include "PlayerWeapon_Sword.h"
#include "PlayerWeapon_Shield.h"
#include "PlayerWeapon_Chakra.h"
#include "PlayerWeapon_Arrow.h"
#include "PlayerIndicator.h"
// Skill
#include "ShellingSkillRange.h"
#include "ShellingSkillAttackPoint.h"
#include "ShellingArrow.h"
#include "SpearWave.h"
// Trigger Obj
#include "MonsterBatchTrigger.h"
#include "Trigger_ChangeCameraView.h"
#include "TestLedgeTrigger.h"
#include "ChangeNavIndexTrigger.h"
#include "PillarTrigger.h"
#include "BlockZone.h"
#include "DeadZone.h"
#include "ResurrectionTrigger.h"
#include "WallRunTrigger.h"
#include "SceneChangeTrigger.h"
#include "MandalaPuzzleTrigger.h"
#include "DemonTreePuzzleTrigger.h"
#include "BossCreateTrigger.h"
#include "CinematicTrigger.h"
#include "CurtainTrigger.h"
#include "GearPuzzleTrigger.h"
#include "FogTrigger.h"
#include "EventTrigger.h"
#include "GoldfishTrigger.h"

//Interact Obj
#include "DynamicPlatform.h"
#include "Elevator.h"
#include "LilyPad.h"
#include "Lotus.h"
#include "RepelWall.h"
#include "MiniGameBuilding.h"
#include "InstanceMonsterBatchTrigger.h"
#include "PathArrow.h"
#include "MahaHead.h"
#include "Grovetender.h"
#include "MiniGame_Jino_Player.h"
#include "Rope.h"
#include "GoalTrigger.h"
#include "NormalMonkey.h"
#include "BeachBall.h"
#include "JumpingMonkey.h"
#include "FireRing.h"
#include "CircusBackground.h"
#include "RajiMask.h"
#include "RajiHand.h"
#include "Rajibalsura.h"
#include "EndingPortal.h"
#include "Vishnu_RollingEye.h"

//////////////////////////////////////////////////////////////////////////////
////STA0GE_6//////////////////////////////////////////////////////////////////
#include "TestObject_PhysX.h"
#include "EnvMappedWater.h"

///////////////////////////////////////////////////////////////////////////
#include "ESCursor.h"
#include "EditorTerrain.h"
#include "Camera_Editor.h"
#include "StaticMapObject.h"
#include "NaviPoint.h"
#include "AssimpCreateMgr.h"


////����//////////////////////////////////////////////////////////////////////
#include "Monster_Mahinasura_Minion.h"
#include "Monster_Mahinasura_Leader.h"
#include "Monster_Vayusura_Minion.h"
#include "Monster_Vayusura_Leader.h"
#include "Monster_Tezabsura_Minion.h"
#include "Monster_Tezabsura_Purple.h"
#include "Monster_Tezabsura_Bomber.h"
#include "Monster_Tezabsura_Landmine.h"
#include "Monster_Jalsura.h"
#include "Monster_Ninjasura.h"
#include "Monster_Ninjasura_Minion.h"
#include "Monster_Gadasura_Black.h"
#include "Monster_Gadasura_Rage.h"
#include "Monster_Wasp.h"
#include "Monster_Wormgrub.h"
#include "Monster_Spider.h"
#include "Monster_Wolf.h"
////////////////////////////////////////////////////////////////////////////////

//Monster_Bullet////////////////////////////////////////////////////////////////
#include "Monster_Bullet_Universal.h"
#include "Monster_Texture_Bullet.h"
#include "Monster_Weapon_Universal.h"
#include "Gadasura_Rage_Hollogram.h"
#include "Monster_Plat_Bullet.h"
////////////////////////////////////////////////////////////////////////////////

//EH MiniGame Class//////////////////////////////////////////////////////////////////////
#include "WorldTexture_Universal.h"
#include "MiniGame_Golu.h"
#include "Golu_Bullet.h"
#include "UI_Texture_Universal.h"
#include "MiniGame_DonkeyKong.h"
#include "MiniGame_KongRaji.h"
#include "KongRajiTrigger.h"
#include "DonkeyKong_BulletTrigger.h"
#include "MiniGame_DonkeyKong.h"
#include "MiniGame_KongGolu.h"
#include "DonkeyKong_Bullet.h"
#include "MiniGame_KongWeapon.h"
////////////////////////////////////////////////////////////////////////////////

/////////MiniGame PACKMEN///////////////////////////////////////////////////////////////////////
#include "PackMen.h"
#include "PM_Monster.h"
#include "PM_Food.h"

/////////MiniGame Taigo//////////////////////////////////
#include "MiniGame_JJB_Player.h"
#include "MiniGamePlayerWeapon.h"
#include "Taiko_Monster.h"
#include "GaolCollider.h"
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
#include "TestNonAnimInstancing.h"
//////////////////////////////////////////////////////////////////////////

//NPC
#include "Goldfish.h"
//

_uint CALLBACK LoadingThread(void* _Prameter)
{
	THREADARG tThreadArg{};
	memcpy(&tThreadArg, _Prameter, sizeof(THREADARG));
	delete _Prameter;


	CLoader* pLoader = (CLoader*)(tThreadArg.pArg);
	 

	switch (pLoader->Get_SceneID())
	{
	case SCENEID::SCENE_LOBY:
		pLoader->Load_Scene_Loby(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;
	case SCENEID::SCENE_STAGESELECT:
		pLoader->Load_Scene_StageSelect(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;
	case SCENEID::SCENE_STAGE1:
		pLoader->Load_Scene_Stage1(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;
	case SCENEID::SCENE_STAGE2:
		pLoader->Load_Scene_Stage2(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;
	case SCENEID::SCENE_STAGE3:
		pLoader->Load_Scene_Stage3(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_STAGE4:
		pLoader->Load_Scene_Stage4(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_STAGE5:
		pLoader->Load_Scene_Stage5(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_STAGE6:
		pLoader->Load_Scene_Stage6(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_STAGE7:
		pLoader->Load_Scene_Stage7(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_BOSS:
		pLoader->Load_Scene_Boss(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_ENDING:
		pLoader->Load_Scene_Ending(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;
	
	case SCENEID::SCENE_LABORATORY_JINO:
		pLoader->Load_Scene_Laboratory_Jino(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_MINIGAME1:
		pLoader->Load_Scene_Minigame1(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_MINIGAME_PM:
		pLoader->Load_Scene_Minigame_PM(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_MINIGAME_Jino:
		pLoader->Load_Scene_Minigame_Jino(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_MINIGAME_JJB:
		pLoader->Load_Scene_Minigame_JJB(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_MINIGAME_DONKEYKONG:
		pLoader->Load_Scene_Minigame_DonkeyKong(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	case SCENEID::SCENE_EDIT:
		pLoader->Load_Scene_Edit(tThreadArg.IsClientQuit, tThreadArg.CriSec);
		break;

	default:
		MSGBOX("Failed to Create Scene");
		break;
	}

	return 0;
}


CLoader::CLoader()
{
}



HRESULT CLoader::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, SCENEID eSceneID)
{
	m_eSceneID = eSceneID;
	m_bIsLoadingFinished = false;
	m_pDevice = pDevice;
	m_pDeviceContext = pDeviceContext;

	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pDeviceContext);

	g_pGameInstance->PlayThread(LoadingThread, this);

	return S_OK;
}

HRESULT CLoader::Load_Scene_Loby(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{

	CGameInstance* pGameInstance = GetSingle(CGameInstance);


#pragma region PROTOTYPE_COMPONENT

	_Matrix			TransformMatrix;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	///* Å×½ºÆ® ¾Ë°Ô¶ô */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Mesh_AlgaeRock_Ledge),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "TestObject", "AlgaeRock_Ledge.FBX", TransformMatrix)));
	//FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Mesh_AlgaeRock_Ledge),
	//	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "TestObject", "AlgaeRock_Ledge.FBX", TransformMatrix)));



	// Related Player Skill
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Texture_ShellingRange),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"ShellingSkillRange.txt")));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Texture_ShellingPoint),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"ShellingSkillTargetPoint.txt")));
	// #TEST Create NoAssimp 

	static _bool bisLoaded = false; 
	if (!bisLoaded)
	{
		bisLoaded = true;

		//// #LOAD ALLMODEL
		//// ��� �� �ε� TEST
		TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Player), TransformMatrix);


		// Player Weapons //
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Spear), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Bow), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Sword), TransformMatrix);
		TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Shield), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Chakra), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Arrow), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.3f, 0.3f, 0.3f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerSkill_SpearWave), TransformMatrix);
		//

		// Player Effects
		TransformMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerEffect_ShellingParabola), TransformMatrix);



		TransformMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		for (_uint i = Prototype_Mesh_JY_Tornado; i <= Prototype_Mesh_Wing; i++)
		{
			GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(COMPONENTPROTOTYPEID(i)), TransformMatrix);
		}

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		for (_uint i = Prototype_Mesh_Vishnu_Rolling_Eye; i <= Prototype_Mesh_Vishnu_Statue; i++)
		{
			GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(COMPONENTPROTOTYPEID(i)), TransformMatrix);
		}



		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_ConeMesh), TransformMatrix);

		// First Monster_Bullet
	//	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	//	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Vayusura_Leader), TransformMatrix);

		TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Minion), TransformMatrix);

		TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Purple), TransformMatrix);

		TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Bomber), TransformMatrix);

		TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Landmine), TransformMatrix);

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Ninjasura_Knife), TransformMatrix);

		//	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		//	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Gadasura_Sinkhole), TransformMatrix);

		TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Gadasura_Terrain), TransformMatrix);

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(L"ArrowDir.fbx", TransformMatrix);
		/////////////////////////////////////


		// #MESHEFFECT MeshLoad 
		// when Merge Off
//		for (_uint i = (_uint)Prototype_Mesh_KurtzpelStart + 1; i < (_uint)Prototype_Mesh_KurtzpelEnd; i++)
//		{
//			STATIC_EFFECTLOAD((COMPONENTPROTOTYPEID)i);
//		}


		// USE LOAD
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

		//JY
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Aura_Linear_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_LightCastRing_01);
		//

		STATIC_EFFECTLOAD(Prototype_Mesh_circle);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Bow_Em_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Bow_Em_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_circle);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_IceSpike_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Bow_Em_Wing_T);
		STATIC_EFFECTLOAD(Prototype_Mesh_mySphere);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_sphere_melon);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_CoreRing_3);
		STATIC_EFFECTLOAD(Prototype_Mesh_MS_ST3_Portal_00);
		STATIC_EFFECTLOAD(Prototype_Mesh_ice2);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Ring_03);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ky_windSmokeDist);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_L_DS_Dashcombo_Y_L);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_ImpactFX_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ice2);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ICE_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SS_Trail_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ArrowBurstTrail_01_New);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SpinningSlash_O_R_DX);
		STATIC_EFFECTLOAD(Prototype_Mesh_Sample_Mesh_Fake_Mesh_Lighting);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Rage_Buff_L_D);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Rage_Buff_L_X);
		STATIC_EFFECTLOAD(Prototype_Mesh_02_L_Upper_SM);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ky_tornado3);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_06_06_SM002);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SG_tornado);
		STATIC_EFFECTLOAD(Prototype_Mesh_mySphere);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SP_End_X_L);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SP_End_Z_R);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Meteo_Sphere3);
		STATIC_EFFECTLOAD(Prototype_Mesh_MS_Shot_Cylinder_00);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DW_Weapon);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Baren_Weapon);
		STATIC_EFFECTLOAD(Prototype_Mesh_Mesh_Leap_Ground_Light);
		STATIC_EFFECTLOAD(Prototype_Mesh_circle_inv);
		STATIC_EFFECTLOAD(Prototype_Mesh_MS_Tornado_Cyl_2side);
		STATIC_EFFECTLOAD(Prototype_Mesh_Mesh_HFB_Grand_Git);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_DarkTails_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_rockRing);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_EM_Copycat_03);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ky_lans_rot);
		STATIC_EFFECTLOAD(Prototype_Mesh_doomBvert);
		STATIC_EFFECTLOAD(Prototype_Mesh_ConeMesh);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Crack_OutLine);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_BBT_Paw);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_AOG_Ring);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_SS_Aura_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Sphere_RPG);
		STATIC_EFFECTLOAD(Prototype_Mesh_MS_Trail_Twist_00);
		STATIC_EFFECTLOAD(Prototype_Mesh_Sample_Mesh_WP_Cylinder_Z);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_AXTrail_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ky_sphere_dist_wind);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DivineLaserBeam_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_TS_Basic_combo_EX2_Sword);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_LB_Invisibility_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Helix_Crystal);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_TS_Double_Slash_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_GT_SphereHarf);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_GN_Wind01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Basic_01_2_Trail_X);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_LightningBolt_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Switching_L_D_Plane);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_IceTrap_Ice);
		STATIC_EFFECTLOAD(Prototype_Mesh_MS_Tornado_Cyl_2side_03);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_IceShards_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_IceShards_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_4E_IceShards_03);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_meteo);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_half_ball_closed_1);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_RainDrop);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Basic_03_3_X_L);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Sphere_Plane_01);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ky_rock07);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ControlPointMatch_Square_02);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Reorgeaskil04_stone1_7);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Box_Basic);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Statue_Female_ReBirth_Body);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Lotus_01_flower);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_GT_Cyinder_01);

		STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_DT_StatueFemale_Pose01);
		//STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_DT_StatueFemale_Pose02);
		//STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_DT_StatueFemale_Pose03);
		//STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_DT_StatueFemale_Pose04);

		

		
		// Bullet
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Monster_Bullet_Vayusura_Leader);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Monster_Bullet_Tezabsura_Minion);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Monster_Bullet_Tezabsura_Purple);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Monster_Bullet_Tezabsura_Bomber);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Monster_Bullet_Tezabsura_Landmine);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Ninjasura_Knife);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_sinkhole);
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Gadasura_Terrain_Bullet);

		// ALLLOAD
		// for (_uint i = (_uint)Prototype_Mesh_KurtzpelStart + 1; i < (_uint)Prototype_Mesh_KurtzpelEnd; i++)
		// 	STATIC_EFFECTLOAD((COMPONENTPROTOTYPEID)i);


		// StaticTest
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_CC_CogMedium_01);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_Fern_01);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_CC_Diya_02);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_Dry_Green_Bush_03);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_BLD_Lion_Statue);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_ENV_F_DecorativePillar_02);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_CC_Pillar_03);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_D_GodHand_01);
	//	STATIC_EFFECTLOAD(Prototype_Mesh_SM_ENV_DT_Bull);



	}


#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(L"TestNonAnimInstance", CTestNonAnimInstancing::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_StaticMapObject), CStaticMapObject::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_InstanceStaticMapObject), CStaticInstanceMapObject::Create(m_pDevice, m_pDeviceContext)));

	//LobbyUI
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_LobbyUI), CLobbyUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_SkillUI), CSkillUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PauseUI), CPauseUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_GraphicUI), CGraphicUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_SoundUI), CSoundUI::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_IngameUI), CIngameUI::Create(m_pDevice, m_pDeviceContext)));
	
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_TestObject), CTestObject::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Player), CPlayer::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Spear), CPlayerWeapon_Spear::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Bow), CPlayerWeapon_Bow::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Sword), CPlayerWeapon_Sword::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Shield), CPlayerWeapon_Shield::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Chakra), CPlayerWeapon_Chakra::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerWeapon_Arrow), CPlayerWeapon_Arrow::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerEffect_ShellingRange), CShellingSkillRange::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerEffect_ShellingPoint), CShellingSkillAttackPoint::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_ChangeCameraView), CTrigger_ChangeCameraView::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_TestLedgeTrigger), CTestLedgeTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_MonsterBatchTrigger), CMonsterBatchTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_ChangeNavIndex), CChangeNavIndexTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_PILLARTRIGGER), CPillarTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_BLOCKZONE), CBlockZone::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_DEADZONE), CDeadZone::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_ResurrectionTrigger), CResurrectionTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_WallRun), CWallRunTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_SceneChangeTrigger), CSceneChangeTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_MandalaPuzzle), CMandalaPuzzleTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_DemonTreePuzzle), CDemonTreePuzzleTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_InstanceMonsterBatchTrigger), CInstanceMonsterBatchTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_BossCreateTrigger), CBossCreateTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_CinematicTrigger), CCinematicTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_CurtainTrigger), CCurtainTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_GearPuzzleTrigger), CGearPuzzleTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_FogTrigger), CFogTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_EventTrigger), CEventTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Trigger_GoldfishTrigger), CGoldfishTrigger::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerSkill_ShellingArrow), CShellingArrow::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_PlayerSkill_SpearWave), CSpearWave::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PlayerIndicator), CPlayerIndicator::Create(m_pDevice, m_pDeviceContext)));


	//JJB
	//ParticleCollider
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_ParticleCollider), CParticleCollider::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_ParticleColliderInOut), CParticle_ColliderInOut::Create(m_pDevice, m_pDeviceContext)));


#pragma endregion


#ifndef _DEBUG
	FAILED_CHECK(Load_AllMonster());
	FAILED_CHECK(Load_AllBoss());
	FAILED_CHECK(Load_AllDynamicMapObject());

	for (_uint i = 0; i < SCENE_END; i++)
	{
		if(i == SCENE_EDIT)continue;
		FAILED_CHECK(Load_MapMesh(SCENEID(i)));
	}


#endif


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);

	return S_OK;
}

HRESULT CLoader::Load_Scene_StageSelect(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

#pragma region PROTOTYPE_COMPONENT
	_Matrix			TransformMatrix;
	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

	/* For.Prototype_Component_Navigation */
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGESELECT, TAG_CP(Prototype_Navigation),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_2.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGESELECT, TAG_CP(Prototype_Mesh_Boss_Rangda),
	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "Boss_RangDa", "Boss_Randa.FBX", TransformMatrix)));

	//TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	//FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGESELECT, TAG_CP(Prototype_Mesh_Player),
	//CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "PlayerMesh", "Player.FBX", TransformMatrix, 2)));




	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda_Finger), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Chieftian), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon4), TransformMatrix);


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	STATIC_EFFECTLOAD(Prototype_Mesh_SM_Aura_Linear_01);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon4), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Snake), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Mahabalasura), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(270.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraAttackArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurCopy), TransformMatrix);

	//Volcano
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Volcano), TransformMatrix);


	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Spear), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Bow), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Sword), TransformMatrix);


	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

	//Boss
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda), CRangda::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_Finger), CRangda_Finger::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Chiedtian), CChiedtian::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon), CChiedtuan_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon_2Page), CChiedtuan_2Page_Weapon::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Snake), CSnake::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Mahabalasura), CMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraArms), CMahabalasura_Arms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraAttackArms), CMahabalasura_AttackArms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraWeapon), CMahabalasura_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraCopy), CCopyMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraSpearWave), CMahabalasura_SpearWave::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraATKSPR), CMahabalasura_AttackSpear::Create(m_pDevice, m_pDeviceContext)));

	//Static_Map
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_Demon_Tree), CDemon_Tree::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_TreeMesh), CTreeMesh::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_MandalaPuzzle), CMandalaPuzzle::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_MandalaMesh), CMandalaMesh::Create(m_pDevice, m_pDeviceContext)));

	//Dynamic_Map
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_FemaleStatue), CFemaleStatue::Create(m_pDevice, m_pDeviceContext)));

	//EffectTest
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Effect_MagicCircle), CRangda_MagicCircle::Create(m_pDevice, m_pDeviceContext)));


	//Interact Obj
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Elevator), CElevator::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_LilyPad), CLilyPad::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Lotus), CLotus::Create(m_pDevice, m_pDeviceContext)));

	//Volcano
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Volcano), CVolcano::Create(m_pDevice, m_pDeviceContext)));
	//FlameTerrain
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_FlameTeraain), CflameTerrain::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage1(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE1, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_1.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE1, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_Boss.FBX", TransformMatrix)));



	FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(Load_MapMesh(SCENE_STAGE1));


#pragma endregion

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE1, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE1, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

#pragma endregion


	RELEASE_INSTANCE(CGameInstance);


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage2(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);

#pragma region PROTOTYPE_COMPONENT
	_Matrix			TransformMatrix;

	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE2, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_2.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE2, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_Boss.FBX", TransformMatrix)));

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE2, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE2, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion

	FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(Load_AllDynamicMapObject());

	FAILED_CHECK(Load_MapMesh(SCENE_STAGE2));

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

#pragma endregion




#pragma endregion
	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage3(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE3, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/BossStage_Rangda.dat")))))
		return E_FAIL;


	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE3, TAG_CP(Prototype_Texture_PathArrow),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"ETC.txt")));


	_Matrix			TransformMatrix;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE3, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));


	FAILED_CHECK(Load_MapMesh(SCENE_STAGE3));

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda_Finger), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Wasp), TransformMatrix);

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE3, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE3, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion

	FAILED_CHECK(Load_AllMonster());


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golu), TransformMatrix);

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

	//Interact Obj
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Elevator), CElevator::Create(m_pDevice, m_pDeviceContext)));

	//Boss
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda), CRangda::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_Finger), CRangda_Finger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_Statue), CRangda_Statue::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_WaspBullet), CRanda_Wasp_Bullet::Create(m_pDevice, m_pDeviceContext)));
	
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Effect_MagicCircle), CRangda_MagicCircle::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Vishnu_RollingEye), CVishnu_RollingEye::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_NPC_Golu), CGolu::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_UI_PathArrow), CPathArrow::Create(m_pDevice, m_pDeviceContext)));
	
#pragma endregion


	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage4(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE4, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/BossNaviData_Sanke.dat")))))
		return E_FAIL;

	_Matrix			TransformMatrix;
	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));


	//DynamicObject
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_FemaleStatue), TransformMatrix);

	FAILED_CHECK(Load_MapMesh(SCENE_STAGE4));


	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Snake), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon), TransformMatrix);
	
	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golem), TransformMatrix);

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE4, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));
#pragma region EH

	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE4, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE4, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion


	FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(Load_AllDynamicMapObject());


#pragma  region PROTOTYPE_GAMEOBJECT

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon), CChiedtuan_Weapon::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Snake_Poison_Raser), CSnake_Poison_Raser::Create(m_pDevice, m_pDeviceContext)));
	
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Elevator), CElevator::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Snake), CSnake::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Grovetender), CGrovetender::Create(m_pDevice, m_pDeviceContext)));
#pragma endregion


	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	 

	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage5(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE5, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/BossNaviData_Mahabalasura.dat")))))
		return E_FAIL;

	_Matrix			TransformMatrix;
	
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE5, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));


	FAILED_CHECK(Load_MapMesh(SCENE_STAGE5));

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Mahabalasura), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(270.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraAttackArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurCopy), TransformMatrix);

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE5, TAG_CP(Prototype_Texture_EndingPortal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"EndingPortal.txt")));

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE5, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE5, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion

	FAILED_CHECK(Load_AllMonster());

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Mahabalasura), CMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraArms), CMahabalasura_Arms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraAttackArms), CMahabalasura_AttackArms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraWeapon), CMahabalasura_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraCopy), CCopyMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraSpearWave), CMahabalasura_SpearWave::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraATKSPR), CMahabalasura_AttackSpear::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MahaHead), CMahaHead::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_RajiMask), CRajiMask::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_RajiHand), CRajiHand::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Rajibalsura), CRajibalsura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_EndingPortal), CEndingPortal::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Scene_Stage6(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;
	FAILED_CHECK(Load_MapMesh(SCENE_STAGE6));


#pragma region PROTOTYPE_COMPONENT


	TransformMatrix = XMMatrixScaling(1, 1, 1) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Vayusura_Leader), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));

	TransformMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f);
	/* �׽�Ʈ �˰Զ� */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Mesh_AlgaeRock_Ledge),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "TestObject", "AlgaeRock_Ledge.FBX", TransformMatrix)));

	/* For.Prototype_Component_Navigation */
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE6, TAG_CP(Prototype_Navigation),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_6.dat")))))
		return E_FAIL;

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion


	//if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE6, TEXT("Prototype_Component_Navigation"),
	//	CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/Test_Jino.dat")))))
	//	return E_FAIL;

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Static_PhysX), CTestObject_PhysX::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Dynamic_PhysX), CTestObject_PhysX::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Joint_PhysX), CTestObject_PhysX::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Elevator), CElevator::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_LilyPad), CLilyPad::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_EnvMappedWater), CEnvMappedWater::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Effect_MagicCircle), CRangda_MagicCircle::Create(m_pDevice, m_pDeviceContext)));
	

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Lotus), CLotus::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(Load_AllMonster());
	FAILED_CHECK(Load_AllDynamicMapObject());
	FAILED_CHECK(Load_AllBoss());




#pragma endregion

	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_Texture_EnvMappedWater),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"EnvMappedWater.txt")));
	//EffectTest
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_0),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 128, 128)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_1),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 66, 60)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_2),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 58, 56)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_3),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 141, 146)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_4),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 264, 240)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE6, TAG_CP(Prototype_VIBuffer_Terrain_5),
		CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 128, 161)));


	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;

}

HRESULT CLoader::Load_Scene_Stage7(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;




#pragma  region Static_Mesh


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_09A.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_BrokenPillars_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_04.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_Railing_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_09B.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_02.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_DoorWay_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_09E.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Defences_02.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Defences_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_RoofWall_Assembled_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_DurgaAvatarTemple_Floor_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Balcony_1B.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Balcony_1C.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Balcony_1D.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_3_Window_06.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Lion_Statue.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Dome_09.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_A.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Building_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Corner_Wall_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Door_NS_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_10.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Wall_Holes_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Wall_Holes_Half_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Defences_02.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Gada_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Bell_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierNarrow_04.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierNarrow_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierCorner_02.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_GlassPanel_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_06.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierFenceEnd_01.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"BG_Mountain_3.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"Elevator.fbx", TransformMatrix);

#pragma endregion

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_STAGE7, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/BossNaviData_Chiedtian.dat")))))
		return E_FAIL;

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE7, TAG_CP(Prototype_Texture_ChiedTianFlame),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"ChiedTianFlame.txt")));

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE7, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));

#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE7, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STAGE7, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion


	FAILED_CHECK(Load_AllBoss());
	FAILED_CHECK(Load_AllMonster());
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Chieftian), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon4), TransformMatrix);



	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	STATIC_EFFECTLOAD(Prototype_Mesh_SM_Aura_Linear_01);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon4), TransformMatrix);

	//Volcano
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Volcano), TransformMatrix);

	FAILED_CHECK(Load_MapMesh(SCENE_STAGE7));

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_InteractObj_Elevator), CElevator::Create(m_pDevice, m_pDeviceContext)));
	// Monster
	//FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Chiedtian), CChiedtian::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon), CChiedtuan_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon_2Page), CChiedtuan_2Page_Weapon::Create(m_pDevice, m_pDeviceContext)));

	//Volcano
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Volcano), CVolcano::Create(m_pDevice, m_pDeviceContext)));
	//FlameTerrain
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_FlameTeraain), CflameTerrain::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion

#pragma  region PROTOTYPE_COMPONENT


#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Scene_Boss(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{



	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

#pragma region PROTOTYPE_COMPONENT


#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

#pragma endregion


	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Scene_Ending(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


#pragma region PROTOTYPE_COMPONENT


#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

#pragma endregion


	RELEASE_INSTANCE(CGameInstance);




	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 99999999;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	return S_OK;
}

HRESULT CLoader::Load_Scene_Minigame1(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golu), TransformMatrix);

#pragma region PROTOTYPE_COMPONENT

	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_MINIGAME1, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_MiniGame1.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_Boss.FBX", TransformMatrix)));


#pragma region EH
	/* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_Texture_Monster_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));

	/* For.Prototype_Component_Prototype_Golu_Bullet */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_Golu_Bullet),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"Golu_Bullet.txt")));

	/* For.Prototype_Component_Prototype_UI_Texture_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_UI_Texture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"UI_Texture_Universal.txt")));

#pragma endregion

	FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(Load_MapMesh(SCENE_MINIGAME1));


#pragma endregion

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_Golu), CMiniGame_Golu::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Golu_Bullet), CGolu_Bullet::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_UI_Texture_Universal), CUI_Texture_Universal::Create(m_pDevice, m_pDeviceContext)));
#pragma endregion


	RELEASE_INSTANCE(CGameInstance);


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Minigame_PM(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;

#pragma  region Static_Mesh

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golu), TransformMatrix);

#pragma  endregion
#pragma region PROTOTYPE_COMPONENT

	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_MINIGAME_PM, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_MiniGame_JY.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME_PM, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "MiniGame_PM", "BurgerMesh.FBX", TransformMatrix)));


	TransformMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f) *
		XMMatrixRotationY(XMConvertToRadians(180.0f)) *
		XMMatrixRotationX(XMConvertToRadians(270.f))*
		XMMatrixTranslation(0.f,0.7f, 0.f);

	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PMMonster), TransformMatrix);

	FAILED_CHECK(Load_MapMesh(SCENE_MINIGAME_PM));


#pragma endregion

#pragma region EH
	/////////////* For.Prototype_Component_Texture_Monster_Texture_Bullet */
	////////////FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_Texture_Monster_Bullet),
	////////////	CTexture::Create(m_pDevice, m_pDeviceContext, L"Monster_Texture_Bullet.txt")));

	/////////////* For.Prototype_Component_WorldTexutre_Universal */
	////////////FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_WorldTexture_Universal),
	////////////	CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));

	/////////////* For.Prototype_Component_Prototype_Golu_Bullet */
	////////////FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME1, TAG_CP(Prototype_Golu_Bullet),
	////////////	CTexture::Create(m_pDevice, m_pDeviceContext, L"Golu_Bullet.txt")));

#pragma endregion

#pragma endregion

	//Prototype_Object_PM_Player,
	//	Prototype_Object_PM_Food,
	//	Prototype_Object_PM_Monster,
#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PM_Player), CPackMen::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PM_Monster), CPM_Monster::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PM_Food), CPM_Food::Create(m_pDevice, m_pDeviceContext)));
	
#pragma endregion


	RELEASE_INSTANCE(CGameInstance);


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Minigame_Jino(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;
	//MiniGameJino_Player
#pragma  region Static_Mesh

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MiniGame_Jino_Player), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_F_Bow_Platform_03), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Rope), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Mahinasura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Tezabsura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_BeachBall), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_FireRing), TransformMatrix);

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Texture_MiniGameJino_Background),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"MiniGame_Jino.txt")));

#pragma  endregion
#pragma region PROTOTYPE_COMPONENT
	FAILED_CHECK(Load_AllMonster());

#pragma endregion


#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_Jino_Player), CMiniGame_Jino_Player::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_Jino_Rope), CRope::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_GoalTrigger), CGoalTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_NormalMonkey), CNormalMonkey::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_JumpingMonkey), CJumpingMonkey::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_BeachBall), CBeachBall::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_FireRing), CFireRing::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_CircusBackground), CCircusBackground::Create(m_pDevice, m_pDeviceContext)));
#pragma endregion


	RELEASE_INSTANCE(CGameInstance);


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Minigame_DonkeyKong(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Player), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golu), TransformMatrix);



	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PlayerWeapon_Spear), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Landmine), TransformMatrix);

#pragma region PROTOTYPE_COMPONENT

	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_MINIGAME_DONKEYKONG, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/NaviData_Stage_MiniGame_DonkeyKong.dat")))))
		return E_FAIL;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME_DONKEYKONG, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_Boss.FBX", TransformMatrix)));

#pragma  region EH
	/* For.Prototype_Component_WorldTexutre_Universal */
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_MINIGAME_DONKEYKONG, TAG_CP(Prototype_WorldTexture_Universal),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"WorldTexture_Universal.txt")));
#pragma endregion
#pragma endregion

	FAILED_CHECK(Load_AllMonster());

	FAILED_CHECK(Load_MapMesh(SCENE_MINIGAME_DONKEYKONG));


#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_KongRaji), CMiniGame_KongRaji::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_KongGolu), CMiniGame_KongGolu::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_DonkeyKong), CMiniGame_DonkeyKong::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_KongRajiTrigger), CKongRajiTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_DonkeyKong_BulletTrigger), CDonkeyKong_BulletTrigger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_DonkeyKong_Bullet), CDonkeyKong_Bullet::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_KongWeapon), CMiniGame_KongWeapon::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion


	RELEASE_INSTANCE(CGameInstance);


	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	for (int i = 0; i < m_iLoadingMaxCount; ++i)
	{
		EnterCriticalSection(_CriSec);
		m_iLoadingProgressCount = i;
		LeaveCriticalSection(_CriSec);
	}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	return S_OK;
	return S_OK;
}

HRESULT CLoader::Load_Scene_Minigame_JJB(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;

#pragma  region Mesh

	TransformMatrix = XMMatrixScaling(0.001f, 0.001f, 0.001f) * XMMatrixRotationY(XMConvertToRadians(180.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MiniGame_JJB_Player), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.005f, 0.005f, 0.005f) *
		XMMatrixRotationY(XMConvertToRadians(180.0f)) *
		XMMatrixRotationX(XMConvertToRadians(270.f))*
		XMMatrixTranslation(0.f, 0.7f, 0.f);

	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PMMonster), TransformMatrix);



#pragma  endregion

#pragma region PROTOTYPE_COMPONENT

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	//Taiko 
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_TaikoUI), CTaikoUI::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_JJB_Player), CMiniGame_JJB_Player::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_PlayerWeapon), CMiniGamePlayerWeapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_PM_Monster), CTaiko_Monster::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_MiniGame_GoalCollider), CGaolCollider::Create(m_pDevice, m_pDeviceContext)));


#pragma  endregion

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLoader::Load_Scene_Edit(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
#pragma region PROTOTYPE_COMPONENT

	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain),
		CVIBuffer_EditorTerrain::Create(m_pDevice, m_pDeviceContext, 4, 4)));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_Texture_EditScene),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"EditScene.txt")));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_Texture_Edit_Terrain),
		CTexture::Create(m_pDevice, m_pDeviceContext, L"EditTerrain.txt")));

	_Matrix			TransformMatrix;

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_Mesh_SkyBox),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "SkyBox", "SkyBox_0.FBX", TransformMatrix)));

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_STATIC, TAG_CP(Prototype_Mesh_AlgaeRock_Ledge),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "TestObject", "AlgaeRock_Ledge.FBX", TransformMatrix)));


	TransformMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	for (_uint i = Prototype_Mesh_JY_Tornado; i <= Prototype_Mesh_Wing; i++)
	{
		GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(COMPONENTPROTOTYPEID(i)), TransformMatrix);
	}

	TransformMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	STATIC_EFFECTLOAD(Prototype_Mesh_SM_DS_Switching_L_Z_Plane);

	////// MERGE //
//	FAILED_CHECK(Load_AllMonster());
//	FAILED_CHECK(Load_AllBoss());
//	FAILED_CHECK(Load_AllDynamicMapObject());

	//Map Make
//	for (_uint i = 0; i < SCENE_END; i++)
//		FAILED_CHECK(Load_MapMesh(SCENEID(i)));

//	FAILED_CHECK(Load_MapMesh(SCENEID::SCENE_STAGE6));

	
#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_EditorCursor), CESCursor::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Camera_Editor), CCamera_Editor::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_EditorTerrain), CEditorTerrain::Create(m_pDevice, m_pDeviceContext)));
	//FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(L"ProtoType_EditRendererUI", CRendererEditSceneUI::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_StaticMapObject), 	CStaticMapObject::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_NaviPoint),	CNaviPoint::Create(m_pDevice, m_pDeviceContext)));
#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	//EnterCriticalSection(_CriSec);
	//m_iLoadingMaxCount = 1;
	//m_iLoadingProgressCount = 0;
	//LeaveCriticalSection(_CriSec);

	//for (int i = 0; i < m_iLoadingMaxCount; ++i)
	//{
	//	EnterCriticalSection(_CriSec);
	//	m_iLoadingProgressCount = i;
	//	LeaveCriticalSection(_CriSec);
	//}

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);

	return S_OK;
}

HRESULT CLoader::Load_Scene_Laboratory_Jino(_bool * _IsClientQuit, CRITICAL_SECTION * _CriSec)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_Matrix			TransformMatrix;

#pragma  region Static_Mesh
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DS_Platform_28.fbx", TransformMatrix);
	pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_01.fbx", TransformMatrix);
		
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Golu), TransformMatrix);

#pragma endregion

#pragma region PROTOTYPE_COMPONENT
	if (FAILED(pGameInstance->Add_Component_Prototype(SCENE_LABORATORY_JINO, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/data/NaviMesh/BossStage_Rangda.dat")))))
		return E_FAIL;

#pragma endregion

#pragma  region PROTOTYPE_GAMEOBJECT
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_RepelWall), CRepelWall::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_DynamicPlatform), CDynamicPlatform::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_NPC_Golu), CGolu::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion

#pragma  region PROTOTYPE_COMPONENT


#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	EnterCriticalSection(_CriSec);
	m_iLoadingMaxCount = 1;
	m_iLoadingProgressCount = 0;
	LeaveCriticalSection(_CriSec);

	EnterCriticalSection(_CriSec);
	m_bIsLoadingFinished = true;
	LeaveCriticalSection(_CriSec);


	return S_OK;
}

HRESULT CLoader::Load_Model_DatFile()
{
	// ?�이???�일�?assimp ?�이 모델 초기??/ ?�이??초기??
	CGameInstance* pGameInstance = GetSingle(CGameInstance);
	_Matrix TransformMatrix = XMMatrixScaling(1, 1, 1);

	// ?�일 경로
	auto static_dat = GetSingle(CGameInstance)->Load_ExtensionList(STR_FILEPATH_RESOURCE_FBXDAT_L, "stc");
	auto dynamic_dat = GetSingle(CGameInstance)->Load_ExtensionList(STR_FILEPATH_RESOURCE_FBXDAT_L, "dyn");


	// MODELDESC / LOAD ?�수
	list<MODELDESC*> List_ModelStatic;
	list<MODELDESC*> List_ModelDynamic;

	FAILED_CHECK( Load_Model(static_dat, List_ModelStatic));
	FAILED_CHECK(Load_Model(dynamic_dat, List_ModelDynamic));

#pragma region TESTCODE

	// 모델 컴포?�트 ?�성
	// For. Test
	auto dynamiciter = dynamic_dat.begin();
	
	GetSingle(CUtilityMgr)->Start_DebugTimer(CUtilityMgr::DEBUGTIMER_1);
	for (auto& modeldesc : List_ModelDynamic)
	{
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(
			SCENEID::SCENE_STATIC,
			(*dynamiciter)->FileName,
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, modeldesc, TransformMatrix)));

		dynamiciter++;
		if (dynamiciter == dynamic_dat.end())
			break;
	}

	auto staticiter = static_dat.begin();
	for (auto& modeldesc : List_ModelStatic)
	{
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(
			SCENEID::SCENE_STATIC,
			(*staticiter)->FileName,
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, modeldesc, TransformMatrix)));

		staticiter++;
		if (staticiter == static_dat.end())
			break;
	}
	GetSingle(CUtilityMgr)->End_DebugTimer(CUtilityMgr::DEBUGTIMER_1,L"asdasd");


#pragma endregion TESTCODE
	
	Safe_Delete_List(static_dat);
	Safe_Delete_List(dynamic_dat);

//	Safe_Delete_List(List_ModelStatic);
//	Safe_Delete_List(List_ModelDynamic);

	return S_OK;

}

HRESULT CLoader::Load_Model(const list<MYFILEPATH*>& pathlist, list<MODELDESC*>& List_Modeldesc)
{
	// #LOAD ?�라?�언??로드 ?�수

	_ulong			dwByte = 0;
	for (auto& path : pathlist)
	{
		wstring fullpath = path->FullPath;
		wstring FileName = path->FileName;
		MODELDESC* modelDesc = nullptr;
		HANDLE			hFile = CreateFile(fullpath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (0 == hFile)
			return E_FAIL;

		{
			modelDesc = NEW MODELDESC;

			// UINT
			ReadFile(hFile, modelDesc->mFBXFullPath, sizeof(wchar_t)*MAX_PATH, &dwByte, nullptr);
			ReadFile(hFile, modelDesc->mFBXFileName, sizeof(wchar_t)*MAX_PATH, &dwByte, nullptr);

			ReadFile(hFile, &modelDesc->mModelType, sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &modelDesc->mNumMeshes, sizeof(_uint), &dwByte, nullptr);
			ReadFile(hFile, &modelDesc->mNumMaterials, sizeof(_uint), &dwByte, nullptr);

			if (modelDesc->mModelType == CModel::TYPE_ANIM)
			{
				ReadFile(hFile, &modelDesc->mNumBones, sizeof(_uint), &dwByte, nullptr);
				ReadFile(hFile, &modelDesc->mNumAnimations, sizeof(_uint), &dwByte, nullptr);
			}

			CModel::MODELTYPE ModelType = (CModel::MODELTYPE)modelDesc->mModelType;

			// ?�당
			if (modelDesc->mNumMeshes != 0)
				modelDesc->mMeshDesc = NEW MESHDESC[modelDesc->mNumMeshes];

			if (modelDesc->mNumMaterials != 0)
				modelDesc->mMaterials = NEW MATDESC[modelDesc->mNumMaterials];

			if (ModelType == CModel::TYPE_ANIM)
			{
				if (modelDesc->mNumBones != 0)
					modelDesc->mBones = NEW BONEDESC[modelDesc->mNumBones];

				if (modelDesc->mNumAnimations != 0)
					modelDesc->mAnimations = NEW ANIDESC[modelDesc->mNumAnimations];
			}

			// MESH
			for (_uint i = 0; i < modelDesc->mNumMeshes; ++i)
			{
				MESHDESC* meshdesc = &modelDesc->mMeshDesc[i];

				// uint
				ReadFile(hFile, &meshdesc->mPrimitiveTypes, sizeof(_uint), &dwByte, nullptr);
				ReadFile(hFile, &meshdesc->mNumVertices, sizeof(_uint), &dwByte, nullptr);
				ReadFile(hFile, &meshdesc->mNumFaces, sizeof(_uint), &dwByte, nullptr);
				ReadFile(hFile, &meshdesc->mMaterialIndex, sizeof(_uint), &dwByte, nullptr);

				if (ModelType == CModel::TYPE_ANIM)
				{
					ReadFile(hFile, &meshdesc->mNumAffectingBones, sizeof(_uint), &dwByte, nullptr);
				}

				meshdesc->mVertices = NEW _float3[meshdesc->mNumVertices];
				meshdesc->mNormals = NEW _float3[meshdesc->mNumVertices];
				meshdesc->mTangents = NEW _float3[meshdesc->mNumVertices];
				meshdesc->mUV = NEW _float2[meshdesc->mNumVertices];
				meshdesc->mFaces = NEW FACEINDICES32[meshdesc->mNumFaces];

				// VTX
				ReadFile(hFile, meshdesc->mVertices, sizeof(_float3)*meshdesc->mNumVertices, &dwByte, nullptr);
				if (dwByte == 0)
					return E_FAIL;

				ReadFile(hFile, meshdesc->mNormals, sizeof(_float3) *meshdesc->mNumVertices, &dwByte, nullptr);
				if (dwByte == 0)
					return E_FAIL;

				ReadFile(hFile, meshdesc->mTangents, sizeof(_float3)*meshdesc->mNumVertices, &dwByte, nullptr);
				if (dwByte == 0)
					return E_FAIL;

				// UV 추�?
				ReadFile(hFile, meshdesc->mUV, sizeof(_float2)*meshdesc->mNumVertices, &dwByte, nullptr);
				if (dwByte == 0)
					return E_FAIL;

				// ?�러�?UV 추�???
				//for (_uint j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++j)
				//{
				//	_float3* cash = new _float3[meshdesc->mNumVertices];


				//	ReadFile(hFile, cash, sizeof(_float3)*meshdesc->mNumVertices, &dwByte, nullptr);
				//	if (cash->x == 0)
				//	{
				//		meshdesc->mTextureCoords[j] = nullptr;
				//		Safe_Delete_Array(cash);
				//	}
				//	else
				//	{
				//		meshdesc->mTextureCoords[j] = new _float3[meshdesc->mNumVertices];
				//		for (_uint k = 0; k < meshdesc->mNumVertices; ++k)
				//		{
				//			meshdesc->mTextureCoords[j]->x = cash->x;
				//			meshdesc->mTextureCoords[j]->y = cash->y;
				//			meshdesc->mTextureCoords[j]->z = 0;
				//		}
				//		Safe_Delete_Array(cash);
				//	}
				//}

				// INDEX
				ReadFile(hFile, meshdesc->mFaces, sizeof(FACEINDICES32)*meshdesc->mNumFaces, &dwByte, nullptr);
				if (dwByte == 0)
					return E_FAIL;

				// WEIGHT
				if (modelDesc->mModelType == CModel::TYPE_ANIM)
				{
					_uint NumAffectingBones = meshdesc->mNumAffectingBones;
					if (NumAffectingBones != 0)
					{
						// �??�덱??리스??
						meshdesc->mAffectingBones = NEW _uint[NumAffectingBones];
						meshdesc->mMeshBones = NEW MESHBONEDESC[NumAffectingBones];

						ReadFile(hFile, meshdesc->mAffectingBones, sizeof(_uint)*NumAffectingBones, &dwByte, nullptr);
						// �?Weight
						for (_uint bone = 0; bone < NumAffectingBones; ++bone)
						{
							ReadFile(hFile, &meshdesc->mMeshBones[bone].mNumWeights, sizeof(_uint), &dwByte, nullptr);
							_uint NumWeight = meshdesc->mMeshBones[bone].mNumWeights;
							if (NumWeight == 0)
								continue;

							meshdesc->mMeshBones[bone].mAiWeights = NEW aiVertexWeight[NumWeight];

							ReadFile(hFile, meshdesc->mMeshBones[bone].mAiWeights,
								sizeof(aiVertexWeight)*NumWeight, &dwByte, nullptr);
							int debug = 5;
						}
					}
				}
			}

			// MATERIAL
			for (_uint i = 0; i < modelDesc->mNumMaterials; ++i)
			{
				MATDESC* matdesc = &modelDesc->mMaterials[i];
				ReadFile(hFile, matdesc->MatName, sizeof(wchar_t)*MAX_PATH*AI_TEXTURE_TYPE_MAX, &dwByte, nullptr);
			}

			// BONE
			if (modelDesc->mModelType == CModel::TYPE_ANIM)
			{
				for (_uint i = 0; i < modelDesc->mNumBones; ++i)
				{
					BONEDESC* bonedesc = &modelDesc->mBones[i];
					ReadFile(hFile, bonedesc->mParentBoneName, sizeof(char)*MAX_PATH, &dwByte, nullptr);
					ReadFile(hFile, bonedesc->mCurrentBoneName, sizeof(char)*MAX_PATH, &dwByte, nullptr);
					ReadFile(hFile, &bonedesc->mOffsetMat, sizeof(_float4x4), &dwByte, nullptr);
					ReadFile(hFile, &bonedesc->mTransMat, sizeof(_float4x4), &dwByte, nullptr);
					ReadFile(hFile, &bonedesc->mDepth, sizeof(_uint), &dwByte, nullptr);
				}


				// ANI
				for (_uint i = 0; i < modelDesc->mNumAnimations; ++i)
				{
					ANIDESC* anidesc = &modelDesc->mAnimations[i];
					ReadFile(hFile, anidesc->mAniName, sizeof(char)*MAX_PATH, &dwByte, nullptr);
					ReadFile(hFile, &anidesc->mDuration, sizeof(double), &dwByte, nullptr);
					ReadFile(hFile, &anidesc->mTicksPerSecond, sizeof(double), &dwByte, nullptr);
					ReadFile(hFile, &anidesc->mNumAniBones, sizeof(_uint), &dwByte, nullptr);
				}

				for (_uint i = 0; i < modelDesc->mNumAnimations; ++i)
				{
					ANIDESC* anidesc = &modelDesc->mAnimations[i];
					anidesc->mAniBones = NEW ANIBONES[anidesc->mNumAniBones];
					for (_uint j = 0; j < anidesc->mNumAniBones; ++j)
					{
						ANIBONES* anibone = &anidesc->mAniBones[j];


						ReadFile(hFile, anibone->mBoneName, sizeof(char)*MAX_PATH, &dwByte, nullptr);
						ReadFile(hFile, &anibone->mHierarchyNodeIndex, sizeof(_int), &dwByte, nullptr);
						ReadFile(hFile, &anibone->mNumKeyFrames, sizeof(_uint), &dwByte, nullptr);
						anibone->mKeyFrames = NEW KEYFRAME[anibone->mNumKeyFrames];
						ReadFile(hFile, anibone->mKeyFrames, sizeof(KEYFRAME)* anibone->mNumKeyFrames, &dwByte, nullptr);

						// #TEST
						//Safe_Delete_Array(anibone->mKeyFrames);
					}

				}
			}
			List_Modeldesc.push_front(modelDesc);
		}
		CloseHandle(hFile);
	}

	return S_OK;
}

HRESULT CLoader::Load_AllMonster()
{
	static _bool bBool = false;

	if (bBool) return S_FALSE;
	bBool = true;


	CGameInstance* pGameInstance = g_pGameInstance;
	_Matrix			TransformMatrix;

#pragma region MonsterMesh

	////////Monster_Mesh
	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Mahinasura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.025f, 0.025f, 0.025f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Mahinasura_Leader), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Vayusura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Vayusura_Leader), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Tezabsura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Tezabsura_Purple), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Tezabsura_Bomber), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Tezabsura_Landmine), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f)) * XMMatrixTranslation(0.f, 1.5f, 0.f);
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Jalsura), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Ninjasura), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Ninjasura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Gadasura_Black), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Gadasura_Rage), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Gadasura_Rage_Hollogram), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Wasp), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_WormGrub), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Spider), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Wolf), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Goldfish), TransformMatrix);


	////////////////////////Monster_Bullet
	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Vayusura_Leader), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Minion), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Purple), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Bomber), TransformMatrix);

	TransformMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Tezabsura_Landmine), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Ninjasura_Knife), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Gadasura_Sinkhole), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.015f, 0.015f, 0.015f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_MONSTER_BULLET(Prototype_Mesh_Monster_Bullet_Gadasura_Terrain), TransformMatrix);
	/////////////////////////////////////

	/////////////////////////////////////Monster_Weapon
	TransformMatrix = XMMatrixScaling(0.00015f, 0.00015f, 0.00015f) * XMMatrixRotationX(XMConvertToRadians(180.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Weapon_Gadasura_Black), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.00015f, 0.00015f, 0.00015f) * XMMatrixRotationX(XMConvertToRadians(180.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Weapon_Gadasura_Rage), TransformMatrix);


#pragma endregion

#pragma region MonsterPrototype


	//Monster
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Mahinasura_Minion), CMonster_Mahinasura_Minion::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Mahinasura_Leader), CMonster_Mahinasura_Leader::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Vayusura_Minion), CMonster_Vayusura_Minion::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Vayusura_Leader), CMonster_Vayusura_Leader::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Tezabsura_Minion), CMonster_Tezabsura_Minion::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Tezabsura_Purple), CMonster_Tezabsura_Purple::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Tezabsura_Bomber), CMonster_Tezabsura_Bomber::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Tezabsura_Landmine), CMonster_Tezabsura_Landmine::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Jalsura), CMonster_Jalsura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Ninjasura), CMonster_Ninjasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Ninjasura_Minion), CMonster_Ninjasura_Minion::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Gadasura_Black), CMonster_Gadasura_Black::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Gadasura_Rage), CMonster_Gadasura_Rage::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Gadasura_Rage_Hollogram), CGadasura_Rage_Hollogram::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Wasp), CMonster_Wasp::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Wormgrub), CMonster_Wormgrub::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Spider), CMonster_Spider::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Wolf), CMonster_Wolf::Create(m_pDevice, m_pDeviceContext)));
	//NPC
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Goldfish), CGoldfish::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Bullet_Universal), CMonster_Bullet_Universal::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Texture_Bullet), CMonster_Texture_Bullet::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Weapon_Universal), CMonster_Weapon_Universal::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Monster_Bullet_Plat), CMonster_Plat_Bullet::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_WorldTexture_Universal), CWorldTexture_Universal::Create(m_pDevice, m_pDeviceContext)));


#pragma endregion

	return S_OK;
}

HRESULT CLoader::Load_AllBoss()
{
	static _bool bBool = false;

	if (bBool) return S_FALSE;
	bBool = true;

	CGameInstance* pGameInstance = g_pGameInstance;
	_Matrix			TransformMatrix;


#pragma  region BossMesh

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Rangda_Finger), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Monster_Wasp), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Chieftian), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_ChieftianWeapon4), TransformMatrix);


	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	STATIC_EFFECTLOAD(Prototype_Mesh_SM_Aura_Linear_01);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon2), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon3), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_SecondPage_ChieftianWeapon4), TransformMatrix);

	//Volcano
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Volcano), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Snake), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_Mahabalasura), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(270.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasuraAttackArms), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurWeapon), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_Boss_MahabalasurCopy), TransformMatrix);


#pragma endregion


#pragma region MonsterPrototype
	//Boss
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda), CRangda::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_Finger), CRangda_Finger::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Effect_MagicCircle), CRangda_MagicCircle::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_Statue), CRangda_Statue::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Rangda_WaspBullet), CRanda_Wasp_Bullet::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Chiedtian), CChiedtian::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon), CChiedtuan_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_ChiedtianWeapon_2Page), CChiedtuan_2Page_Weapon::Create(m_pDevice, m_pDeviceContext)));
	//Volcano
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Volcano), CVolcano::Create(m_pDevice, m_pDeviceContext)));
	//FlameTerrain
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_FlameTeraain), CflameTerrain::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Snake), CSnake::Create(m_pDevice, m_pDeviceContext)));

	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_Mahabalasura), CMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraArms), CMahabalasura_Arms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraAttackArms), CMahabalasura_AttackArms::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraWeapon), CMahabalasura_Weapon::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraCopy), CCopyMahabalasura::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Boss_MahabalasuraATKSPR), CMahabalasura_AttackSpear::Create(m_pDevice, m_pDeviceContext)));

#pragma endregion

	return S_OK;
}

HRESULT CLoader::Load_AllDynamicMapObject()
{
	static _bool bBool = false;

	if (bBool) return S_FALSE;
	bBool = true;

	CGameInstance* pGameInstance = g_pGameInstance;
	_Matrix			TransformMatrix;


	//staticMesh MapObject
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_DemonTree_Seg01), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_DemonTree_Seg02), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_DemonTree_Seg03), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_DemonTree_Seg04), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_DemonTree_Seg05), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_CC_PuzzleAssembly_Right_01), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_CC_CogMedium_01), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_CC_CogMedium_02), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_CC_CogMedium_03), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(0.f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_SM_ENV_CC_WaterWheel_01), TransformMatrix);

	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MandalaCircle_0), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MandalaCircle_1), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MandalaCircle_2), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MandalaCircle_3), TransformMatrix);
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_MandalaCircle_4), TransformMatrix);

	//DynamicObject
	TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	GetSingle(CAssimpCreateMgr)->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_FemaleStatue), TransformMatrix);



	//Static_Map
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_Demon_Tree), CDemon_Tree::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_TreeMesh), CTreeMesh::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_MandalaPuzzle), CMandalaPuzzle::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_MandalaMesh), CMandalaMesh::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_Gear_Puzzle), CGear_Puzzle::Create(m_pDevice, m_pDeviceContext)));
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_Gear), CGear::Create(m_pDevice, m_pDeviceContext)));

	//Dynamic_Map
	FAILED_CHECK(pGameInstance->Add_GameObject_Prototype(TAG_OP(Prototype_Object_Map_FemaleStatue), CFemaleStatue::Create(m_pDevice, m_pDeviceContext)));

	return S_OK;
}

HRESULT CLoader::Load_MapMesh(SCENEID eID)
{
	_Matrix TransformMatrix;
	switch (eID)
	{
	case SCENE_STATIC:
		break;
	case SCENE_LOBY:
		break;
	case SCENE_LOADING:
		break;
	case SCENE_STAGESELECT:
		break;
	case SCENE_STAGE1:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma  region Static_Mesh
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Stairs_01_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Diya_02_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_LionEntranceSplit_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform04_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BullPlatform_Broken_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BullPlatform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Bull.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBaseStep_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBaseStep_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_TempleBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Durga_Statue_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Trishul_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Sword_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Shield_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Gada_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Drum_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Chakra_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Bow_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Bell_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_ElephantHead_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Fern_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_PillarLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Diya_02_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_PillarLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Plant_CVR_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Green_Stack_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Plant_CVR_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_F_Vine07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Straight_006.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_F_Vine14.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerVine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Pinkflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Straight_006.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vine_Pillar_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vine_Pillar_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whiteflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundClutter_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_03B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundClutter_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_02A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Green_Stack_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"VentQStone.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ElephantHead.fbx", TransformMatrix);

		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_06.fbx", TransformMatrix);

		
#pragma endregion

	}
		break;
	case SCENE_STAGE2:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma  region Static_Mesh
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_TrishulGrant03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Statue_Female_ReBirth_Body.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Statue_Female_ReBirth_Leg_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Statue_Female_ReBirth_Leg_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_10.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Root_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Root_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_tree_trunk2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Pinkvine_wall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Pinkvine_wall_01a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_ArchStairs_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_F_Palace_WALL_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_TempleEnt.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Drawbridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DiyaBridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_D_BLD_PalaceCOL_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_D_BLD_PalaceCOL_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DiyaBridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DiyaBridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DiyaBridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Dome_014.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Drawbridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ENV_F_DecorativePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ENV_F_DecorativePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ENV_F_DecorativePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ENV_F_DecorativePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_WallPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_WallPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Stairs_01_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BridgeMiddle01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_PaddyField_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"QOuterwall_WallB.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"QOuterwall_WallE.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_PaddyField_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Stairs_01_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_ExitDoor_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_FemaleStatue_Pose_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_FemaleStatue_Pose_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Corner_Wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Corner_Wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_WallPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_TropicalTree_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Frame_01_int.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Drawbridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_FemaleStatue_Pose_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_FemaleStatue_Pose_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BullPlatform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DS_Platform_28.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Fern_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_GroundColumn_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_FemaleStatue_Pose_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_04a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whiteflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"UnderseaRock_Pile.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tropical_Tree_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tropical_Tree_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_01a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tropical_Tree_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_WeaponGroup_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_MS_RootBlocker_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Fireplace_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_WoodBox_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DBPully_DM.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_D_WillowTREE_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_tree_trunk2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_D_BLD_PalaceArch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tropical_Tree_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tropical_Tree_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_01a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_01a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_03A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_F_Flower02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BridgeMiddle03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_TropicalTree_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_TrishulGrant03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_StraightWall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_01a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Sculpture02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DBPully.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Dry_Green_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_PaddyField_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_CC_straightboxwall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"bridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Branch_LG_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Branch_LG_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_boxbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DB_WoodenPlank.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Pinkflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BridgeMiddle03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BridgeMiddle03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_ArchStairs_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_ArchStairs_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_ArchStairs_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DB_WoodenPlank.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roundbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mossplant.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BridgeMiddle03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_TropicalTree_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DS_BrokenArch_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mossplant.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_StoryPanel_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_StraightWall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Broken_Branch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Broken_Branch_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_Wall02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Big_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"UnderseaRock_Pile.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Shield_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Shield_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DiyaBridge.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_BrokenPillars_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_BrokenPillars_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_PRP_PillarStatuesBroken_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FortBridge_Broken_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_BrokenPillars_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FortBridge_Broken_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DS_Platform_28.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Roots_Hanging_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DS_BrokenArch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBPillar04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_BrokenArch_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DB_WoodenPlank.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_ArchStairs_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_TreeBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DBSculpture.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DB_WoodenPlank.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Tower_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Statue_Female_ReBirth_Leg_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Tree_Trunk_1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"UnderseaRock_Pile.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"BallMesh.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"DarkBaldTree.fbx", TransformMatrix);
#pragma  endregion


	}
		break;
	case SCENE_STAGE3:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma region MapPrototype
		_Matrix			TransformMatrix;
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);

		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Vishnu_Statue.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorRailing_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierNarrow_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Horizontal_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierWide_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierNarrow_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_boxbush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_E.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_low01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_low01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_TropicalTree_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_boxbush_01.fbx", TransformMatrix);

		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorVertical_Cog_Top_01.fbx", TransformMatrix);

		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"BallMesh.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ArrowDir.fbx", TransformMatrix);
#pragma endregion RangdaMapPrototype
	}
		break;
	case SCENE_STAGE4:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma region Snake
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SnakeMapMesh.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BackdropTemple_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"QRocksC.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"BG_Mountain_1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"BG_Mountain_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_TombBase_01.fbx", TransformMatrix);

#pragma endregion Snake
	}
		break;
	case SCENE_STAGE5:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma region Mahabalasura
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		//
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DS_BrokenArch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DS_BrokenArch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_StepwellStairs_Half_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_DS_BrokenArch_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_FemaleStatue_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_GodHand_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Statue_Shiva_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_VishnuTemple_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"QRocksC.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"MahaHead.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"MahaHead_Ending.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"Player_Hand.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"Player_Arm.fbx", TransformMatrix);
#pragma  endregion Mahabalasura

	}
		break;
	case SCENE_STAGE6:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;
#pragma region STATICMESH
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_DoorWay_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_DockPlatform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockStairs_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockStepWall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockStepWall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Door_S_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Door_S_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierNarrow_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_PierCorner_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_Withwindow_SM_ENV_CC_StraightWall_WithWindow.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_VishnuTemple_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Wall_Solid_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02_SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_RangdaArena_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Border_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Border_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_DoorWay_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Door_S_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Door_S_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower_Balcony.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_D.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Wall_Solid_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Wall_Solid_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_02a.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_Railing.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorRailing_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorVertical_Cog_Top_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterFountain_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorVertical_Cog_Top_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Wooden_Planks_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorRailing_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_054_SM_ENV_CC_Platform_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_054_SM_ENV_CC_Platform_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Dome_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_C.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Arch_B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterFountain_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Railing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorVertical_Cog_Top_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorRailing_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_ElevatorHousing_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_TreeBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_Circular_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterFountain_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterFountain_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Platform_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Water_Platform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleWalls_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleWalls_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleWalls_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleWalls_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleWalls_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleTop_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleTop_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleTop_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleTop_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleTop_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_BoatRound_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_CC_DockPlanks_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		//pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_PuzzleAssembly_Right_01.fbx", TransformMatrix);
		//pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterWheel_01.fbx", TransformMatrix);
		//pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_WaterWheel_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Garuda_Tower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_StraightWall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Arch.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Arch.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Arch.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Arch.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Bridge_Arch.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Pillar_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_Pink.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_CogLarge_04.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_rock_river_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Elevator_Vertical_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lillypad_02_A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01.fbx", TransformMatrix);

#pragma endregion STATICMESH

	}
		break;
	case SCENE_STAGE7:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma  region Static_Mesh
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Stairs_01_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Diya_02_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_LionEntranceSplit_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform04_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BullPlatform_Broken_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_BullPlatform_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Bull.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBaseStep_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBaseStep_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Stairs_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_TempleBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_DurgaBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Durga_Statue_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_Right_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_Arm_left_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Trishul_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Sword_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Shield_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Lotus_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Gada_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Drum_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Chakra_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Bow_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_WP_Bell_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_PRP_DT_ElephantHead_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_BLD_Arch_Stairs.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_StatueBase.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueBase_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform02_2.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Fern_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_PillarLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Diya_02_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_PillarLarge_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatuePillar_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Plant_CVR_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_05.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Green_Stack_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Plant_CVR_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_F_Vine07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Straight_006.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whitevine_wall_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_F_Vine14.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerVine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Pinkflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Straight_006.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vines_Ruins_Exterior_ENT_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vine_Pillar_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Vine_Pillar_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Whiteflower_vine_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Lotus_01_flower.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_FlowerBush_03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_Bush_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundClutter_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_03B.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GRND_PLANT_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundClutter_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_GroundScatter_02A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Green_Stack_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Grass_01A1.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_Mystic_Roots_Hanging_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"VentQStone.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Platform06_Base.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"ElephantHead.fbx", TransformMatrix);

#pragma endregion
	}
		break;
	case SCENE_BOSS:
		break;
	case SCENE_ENDING:
		break;
	case SCENE_EDIT:
	{
		static _bool bBool = false;
		if (bBool) return S_FALSE;
		bBool = true;

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		GetSingle(CAssimpCreateMgr)->Load_ALL_Model(TransformMatrix, TransformMatrix);


		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_Texture_EnvMappedWater),
			CTexture::Create(m_pDevice, m_pDeviceContext, L"EnvMappedWater.txt")));

		//EffectTest
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_0),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 128, 128)));
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_1),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 66, 60)));
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_2),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 58, 56)));
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_3),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 141, 146)));
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_4),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 264, 240)));
		FAILED_CHECK(pGameInstance->Add_Component_Prototype(SCENEID::SCENE_EDIT, TAG_CP(Prototype_VIBuffer_Terrain_5),
			CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, 128, 161)));

		FAILED_CHECK(GetSingle(CGameInstance)->Add_GameObject_Prototype(TAG_OP(Prototype_Object_EnvMappedWater),
			CEnvMappedWater::Create(m_pDevice, m_pDeviceContext)));

	}
		break;
	case SCENE_MINIGAME1:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma  region Static_Mesh
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
	
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_TempleBase_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_D_SoldierStatue_01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_CC_Window_Ba.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_Mountain_08.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SnakeMapMesh.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_Dome_014.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_3_Window_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_3_Window_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_3_Window_06.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_FloatingWall_Trim_07.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose01.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose03.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_DT_StatueFemale_Pose04.fbx", TransformMatrix);

#pragma endregion

	}
	break;

	case SCENE_MINIGAME_PM:
	{

#pragma  region Static_Mesh
		static _bool bBool = false;
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"Burger_Alphabet.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_PlatFORM_09E.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);	

		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		STATIC_EFFECTLOAD(Prototype_Mesh_SM_Aura_Linear_01);
#pragma endregion


		//Prototype_Mesh_PackMen,
		//	Prototype_Mesh_PM_PowerUpFood,
		//	Prototype_Mesh_PM_Food,
		TransformMatrix = XMMatrixScaling(0.0001f, 0.0001f, 0.0001f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PackMen), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PM_PowerUpFood), TransformMatrix);
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f))*
			XMMatrixRotationX(XMConvertToRadians(270.f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PM_Food), TransformMatrix);





		if (bBool) return S_FALSE;
		bBool = true;
	}
	break;
	case SCENE_MINIGAME_DONKEYKONG:
	{
		static _bool bBool = false;

		if (bBool) return S_FALSE;
		bBool = true;

#pragma  region Static_Mesh
		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		CAssimpCreateMgr* pAssimpCreateMgr = GetSingle(CAssimpCreateMgr);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_F_WallTrim_02.fbx", TransformMatrix);
		pAssimpCreateMgr->Load_Model_One_ByFBXName(L"SM_ENV_WallBasic_11.fbx", TransformMatrix);



		TransformMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		pAssimpCreateMgr->Load_Model_One_ByFBXName(TAG_CP(Prototype_Mesh_PM_PowerUpFood), TransformMatrix);

#pragma endregion
		break;
	}
	case SCENE_END:
		break;
	default:
		break;
	}

	return S_OK;
}


CLoader * CLoader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, SCENEID eSceneID)
{
	CLoader* pTempLoader = NEW CLoader;

	if (FAILED(pTempLoader->Initialize(pDevice,pDeviceContext,eSceneID)))
	{
		Safe_Release(pTempLoader);
		MSGBOX("Failed to Create CLoader");
		return nullptr;
	}

	return pTempLoader;

}

void CLoader::Free()
{
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
	 
}
 