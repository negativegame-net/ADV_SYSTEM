

���K�h���C�u�p�A�h�x���`���[�G���W��


���K�h���C�u�J������SGDK�p�v���O�����ł��B
�G�N�Z���t�@�C���ɋL�q���ꂽ�X�N���v�g����SGDK�p�̃\�[�X�𐶐����邱�Ƃ�
MD�����̃v���O�����������Ȃ��Ă��Œ���̃A�h�x���`���[�Q�[�������邱�Ƃ�ڎw���܂����B

����
�EMicrosoft Excel���K�v�ł��B
�ECode::Blocks�ł̊J����O��ɂ��Ă��܂��B
�@�J�����̍쐬�ɂ��Ă͊������܂��B

�����p���@�i�v���W�F�N�g�ɑg�ݍ��ޕ��@�j
�O.���L�T�C�g�l�́uDraw_Shift_JIS�v��g�ݍ��ޑO��̃v���O�����ɂȂ��Ă܂��B
https://nendo16.jimdofree.com/

�uDraw_Shift_JIS�v���_�E�����[�h���ăv���W�F�N�g�t�H���_���ɉ��L�̃t�@�C����
���K�w�ɔz�u���ĉ������B
	src/draw_sjis.c
	src/draw_sjis.h
	res/sjis_font.png

�P�DADV_SYSTEM/src���̃t�@�C�����v���W�F�N�g�t�H���_���̓��K�w�ɔz�u���Ă��������B

�Q�D�uadv_system_codecreator.xlsm�v�́u�X�N���v�g�v�V�[�g�ɃX�N���v�g���L�q��
�@���V�[�g���́u�����v�{�^���������ƃv���O�����t�@�C�����o�͂���܂��B
�@�o�͏ꏊ�̃p�X�́u�ݒ�v�V�[�g�ɓ��͂��܂��B
�@�o�͂��ꂽadvsys_data.h�Aadvsys_resource.h�����ꂼ��src�Ares�t�H���_���ɔz�u����
�@�K�v������܂��̂ŁA��{�I��1.�ɂ̓v���W�F�N�g�t�H���_/src�A
�@2.�ɂ̓v���W�F�N�g�t�H���_/res��ݒ肷�邱�Ƃ����߂܂��B
�@
	[�X�N���v�g�L�ڕ��@] 
		�V�[�����@�c�@�X�N���v�g�̃W�����v��͂����ɋL�ڂ��ꂽ�n�_���w�肷��B
		�R�}���h���A�l1�A�l2�A�l3�A�l4�@�c�@�R�}���h�Ŏw�肳�ꂽ���������s�B�R�}���h��ނ͉��L�Q��
			STR�c�l1�Ŏw�肵���������\��
			IPTWAIT�c�������\�����A���[�U�[�̃R�}���h���́i���������j��҂�
			IPTJMP�c�K��IPTWAIT�̌�Ɏw�肵�A���������ɑΉ�����w��V�[���ɃW�����v
			�i���F�l1�Ŏw�肵���V�[���A���F�l2�Ŏw�肵���V�[���A���F�l3�Ŏw�肵���V�[���A���F�l4�Ŏw�肵���V�[���j
			IF�c�l1�̕ϐ����ƒl3�Ŏw�肵�����l��l2�̉��Z�q�Ŕ�r���ATRUE�̏ꍇ�l4�Ŏw�肵���V�[���փW�����v�B
				�L�q���鉉�Z�q�͈ȉ�
					EQUAL�c�u���v�i�l1���l3�̏ꍇTRUE�j
					MORE_THAN�c�u���v�i�l1���l3�̏ꍇTRUE�j
					LESS_THAN�c�u���v�i�l1���l3�̏ꍇTRUE�j
					E_MORE_THAN�u�����v�i�l1�����l3�̏ꍇTRUE�j
					E_LESS_THAN�u�����v�i�l1�����l3�̏ꍇTRUE�j
					N_EQUAL�c�u���v�i�l1���l3�̏ꍇTRUE�j
			IMG�c�w�iA�ʂɒl1�Ŏw�肵���摜��`��B���W��0�C0�Œ�A�p���b�g��PAL1�Œ�B
			�i�p���b�g�͉摜���玩����������j
			�摜�͒l1�Ŏw�肵�����̂Ɠ����̃t�@�C����res�t�H���_���Ɏ蓮�Ŕz�u���Ă��������B
			SETVAL�c�l1�Ŏw�肵���ϐ��ɒl2�̐��l���i�[�B
				�l1�ɏ����ꂽ�ϐ��͎������������̂ŕϐ���`�̋L�q�Ȃǂ͕s�v�B
			ADDVAL�c�l1�Ŏw�肵���ϐ��ɒl2�̐��l�����Z�B
				�l1�ɏ����ꂽ�ϐ��͎������������̂ŕϐ���`�̋L�q�Ȃǂ͕s�v�B
			SUBVAL�c�l1�Ŏw�肵���ϐ�����l2�̐��l�����Z�B
				�l1�ɏ����ꂽ�ϐ��͎������������̂ŕϐ���`�̋L�q�Ȃǂ͕s�v�B
			JMP�c�l1�Ŏw�肵���V�[���փW�����v
			END�c�X�N���v�g�̓ǂݍ��݂��~����B��q��update_adv_system()�̕Ԃ�l�ɒl1��ݒ�B

	���G���[�`�F�b�N���͂��ĂȂ��̂ŕs�����Ȓl��ݒ肷��ƃv���O�������R���p�C���G���[�ɂȂ�A�܂���
	���삪���������Ȃ�\��������܂��B

�R�D������Ԃł̓X�N���v�g�̈�ԏ�̃V�[������n�܂�悤�ȋL�q��main.c�ɋL�ڂ���Ă��܂��B
�@����̃v���O��������{�G���W�����Ăяo���ꍇ�͉��L�̊֐���p���Ď��s���\�ł��B
	void init_adv_system()�@�G���W���̏�����
		�c�J�n����O�ɕK�����s����

	void start_adv_system(u16 sceneIdx, u16 vramIdx)�@�G���W���̊J�n
		�csceneIdx�Ŏw�肵���V�[������G���W�����J�n�B
		�@�i�V�[���̃C���f�b�N�X��adv_system_codecreator.xlsm�i�v���O����������j
		�@�́u�V�[�����X�g�vB��ƑΉ��j
		�@�{�G���W���ɂ��摜�\�����AvramIdx�ȍ~�̔Ԓn��VRAM���G���W���ŗ��p����B
		�@�i����Ȃ��B���O�Řg�Ȃǂ�`�悷��Ƃ��͘g�f�[�^�̕�������w�肷��A�݂����ȗp�r�j
	
	u16 update_adv_system()�@�G���W���̍X�V
		�c�Q�[�����[�v���ɋL�ڂ��邱�ƂōX�V���s����B
		�@�X�N���v�g�ŁuEND�v���w�肵���n�_�܂œ��B�����ꍇ�A���̃t���[���Łu�ԋp�l�v�ɐݒ肵��
		�@�l��Ԃ��B����ȊO�i���s���j�͒萔�uADV_SYS_NULL�v��Ԃ��B
		�@�I��������s�������ꍇ�͂���Ŕ��ʂł���B


��sample�t�H���_���ɃT���v���Q�[���v���W�F�N�g�ꎮ������܂��B

�����̑�
	�EBGM�͖点�Ȃ���ł����H
	���匳�̃Q�[���ł͂��̃G���W���O�Ŗ炵�Ă��̂Ŏ�������Ă܂���B���݂܂���B

�����C�Z���X
	MIT License

���o�[�W����
	2021/01/24�@�c�@ver1.0

--------------------------------------

�l�K�e�B�u�ɃQ�[������肽���i�ʊفj
http://negativegame.net/

Mail�Fhinsyuku@c-error.net

--------------------------------------
