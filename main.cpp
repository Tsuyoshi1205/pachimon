#include "DxLib.h"

#define MAP_SIZE 32
#define MAP_WIDTH 20
#define MAP_HEIGHT 15

//マップのデータ
int MapData_1[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0}
};


int MapData_2[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0}
};



int Key[256];
int gpUpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}

int x = 320, y = 240;
//キーが押されている間、画像を動かす
void gpCalc() {
	if (Key[KEY_INPUT_RIGHT] >= 1) {
		x++;
	}
	if (Key[KEY_INPUT_DOWN] >= 1) {
		y++;
	}
	if (Key[KEY_INPUT_LEFT] >= 1) {
		x--;
	}
	if (Key[KEY_INPUT_UP] >= 1) {
		y--;
	}
}


int xcount = 0, ycount = 0;
int ix = 0, iy = 0, result = 8;
//移動方向とキャラチップのすり合わせ
void gpCalc2() {
	//カウント数だけで方向がわかるように0にしてから計算する
	if (Key[KEY_INPUT_RIGHT] >= 1) {
		if (xcount < 0)xcount = 0;
		++xcount;
	}
	if (Key[KEY_INPUT_DOWN] >= 1) {
		if (ycount < 0)ycount = 0;
		++ycount;
	}
	if (Key[KEY_INPUT_LEFT] >= 1) {
		if (xcount > 0)xcount = 0;
		--xcount;
	}
	if (Key[KEY_INPUT_UP] >= 1) {
		if (ycount > 0)ycount = 0;
		--ycount;
	}


	//カウント数から画像配列の添字を求める
	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	//xcountが正なら右向き→3行目の先頭添字番号を足す
	if (xcount > 0) {
		ix += 6;
		result = ix;
	}
	else if (xcount < 0) {
		ix += 3;
		result = ix;
	}

	if (ycount > 0) {
		iy += 0;
		result = iy;
	}
	else if (ycount < 0) {
		iy += 9;
		result = iy;
	}
}


//gpCalcのサブ（キーが押されていなければカウントを0にする）
void gpCalc3() {
	if (Key[KEY_INPUT_LEFT] == 0 && Key[KEY_INPUT_RIGHT] == 0) {
		xcount = 0;
	}
	if (Key[KEY_INPUT_UP] == 0 && Key[KEY_INPUT_DOWN] == 0) {
		ycount = 0;
	}
}

typedef struct {
	char name[20];

	int HitPont;

	char waza_1[20];
	int waza_damage_1;
	int waza_pp_1;
	char waza_type_1[20];

	char waza_2[20];
	int waza_damage_2;
	int waza_pp_2;
	char waza_type_2[20];

	char waza_3[20];
	int waza_damage_3;
	int waza_pp_3;
	char waza_type_3[20];

	char waza_4[20];
	int waza_damage_4;
	int waza_pp_4;
	char waza_type_4[20];

}Pachimon;


void DrawBattleArea(int PlayerImage, int MonImage_2) {
	DrawBox(0, 0, 640, 480, GetColor(0, 100, 255), TRUE);  //画面全体に水色の四角形を描画
	DrawOval(500, 150, 130, 40, GetColor(0, 200, 0), TRUE);		//野生用の楕円
	DrawOval(140, 390, 220, 60, GetColor(0, 200, 0), TRUE);		//プレイヤー用の楕円

	DrawRotaGraph(495, 120, 3.0, 0.0, MonImage_2, TRUE);			//野生用の画像の表示
	DrawRotaGraph(100, 340, 4.0, 0.0, PlayerImage, TRUE);		//プレイヤー画像の表示

	DrawBox(0, 380, 640, 480, GetColor(0, 0, 0), TRUE);  //画面下に黒色の四角形を描画
	DrawBox(10, 390, 630, 470, GetColor(255, 255, 255), TRUE);		//吹き出し用の白い四角形
	
}

void DrawHP(int pachi_B_CurrentHP) {
	//野生のモンスター用
	DrawTriangle(255, 90, 255, 110, 275, 100, GetColor(0, 0, 0), TRUE);
	DrawBox(0, 45, 255, 135, GetColor(0, 0, 0), TRUE);		//野生の名前表示用の白い四角形の枠
	DrawBox(0, 50, 250, 130, GetColor(255, 255, 255), TRUE);		//野生の名前表示用の白い四角形

	SetFontSize(30);                             //文字サイズ変更
	SetFontThickness(10);                         //文字の太さ変更
	DrawFormatString(5, 55, GetColor(50, 50, 50), "パチモンB");
	SetFontSize(20);                             //文字サイズ変更
	SetFontThickness(20);                         //文字の太さ変更
	//DrawFormatString(180, 65, GetColor(0, 0, 0), "Lv20");

	//野生のモンスター用ゲージ
	DrawBox(70, 95, 225, 115, GetColor(0, 0, 0), TRUE);				//HP黒枠
	DrawBox(100, 100, 210, 110, GetColor(150, 150, 150), TRUE);		//HP灰色
	DrawBox(100, 100, 100 + pachi_B_CurrentHP, 110, GetColor(0, 220, 0), TRUE);			//HP緑
	SetFontSize(12);                             //文字サイズ変更
	SetFontThickness(20);                         //文字の太さ変更
	DrawFormatString(80, 99, GetColor(200, 0, 0), "HP");
}

void DrawHP_2(int pachi_A_CurrentHP, int pachi_A_HP) {
	//プレイヤーのモンスター用
	DrawTriangle(385, 310, 385, 330, 365, 320, GetColor(0, 0, 0), TRUE);
	DrawBox(385, 245, 640, 355, GetColor(0, 0, 0), TRUE);		//野生の名前表示用の白い四角形の枠
	DrawBox(390, 250, 640, 350, GetColor(255, 255, 255), TRUE);		//野生の名前表示用の白い四角形

	SetFontSize(30);                             //文字サイズ変更
	SetFontThickness(10);                         //文字の太さ変更
	DrawFormatString(395, 255, GetColor(50, 50, 50), "パチモンA");
	SetFontSize(20);                             //文字サイズ変更
	SetFontThickness(20);                         //文字の太さ変更
	//DrawFormatString(570, 265, GetColor(0, 0, 0), "Lv20");

	//プレイヤーのモンスター用ゲージ
	DrawBox(460, 295, 615, 315, GetColor(0, 0, 0), TRUE);				//HP黒枠
	DrawBox(490, 300, 600, 310, GetColor(150, 150, 150), TRUE);		//HP灰色
	DrawBox(490, 300, 490 + pachi_A_CurrentHP, 310, GetColor(0, 220, 0), TRUE);			//HP緑
	SetFontSize(12);                             //文字サイズ変更
	SetFontThickness(20);                         //文字の太さ変更
	DrawFormatString(470, 299, GetColor(200, 0, 0), "HP");
	SetFontSize(20);                             //文字サイズ変更
	SetFontThickness(20);                         //文字の太さ変更
	DrawFormatString(520, 320, GetColor(50, 50, 50), "%d／%d", pachi_A_CurrentHP, pachi_A_HP);

}


int Scene = 0;
int BattleKey = 0;
int BattleKeyX = 0;
int BattleKeyY = 0;
int Skill = 0;
int SkillSelect = 0;
void DrawBattleKey(int side) {
	if (Key[KEY_INPUT_RIGHT] == 1) {
		BattleKeyX++;
		if (BattleKeyX > 1)BattleKeyX = 0;
	}
	if (Key[KEY_INPUT_LEFT] == 1) {
		BattleKeyX--;
		if (BattleKeyX < 0)BattleKeyX = 1;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		BattleKeyY--;
		if (BattleKeyY < 0)BattleKeyY = 1;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		BattleKeyY++;
		if (BattleKeyY > 1)BattleKeyY = 0;
	}

	if (BattleKeyX == 0 && BattleKeyY == 0) {
		BattleKey = 0;
	}
	if (BattleKeyX == 1 && BattleKeyY == 0) {
		BattleKey = 1;
	}
	if (BattleKeyX == 0 && BattleKeyY == 1) {
		BattleKey = 2;
	}
	if (BattleKeyX == 1 && BattleKeyY == 1) {
		BattleKey = 3;
	}


	switch (BattleKey) {
		//たたかう
	case 0:
		if (side == 0)DrawTriangle(420, 398, 420, 418, 435, 408, GetColor(50, 50, 50), TRUE);
		if (side == 1) {
			DrawTriangle(10, 398, 10, 418, 25, 408, GetColor(50, 50, 50), TRUE);
			SkillSelect = 0;
		}
		
		if (Key[KEY_INPUT_RETURN] == 1 && side == 0) {
			Scene = 7;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 1) {
			Skill = 1;
		}

		break;

		//バッグ
	case 1:
		if (side == 0)DrawTriangle(540, 398, 540, 418, 555, 408, GetColor(50, 50, 50), TRUE);
		if (side == 1) {
			DrawTriangle(210, 398, 210, 418, 225, 408, GetColor(50, 50, 50), TRUE);
			SkillSelect = 1;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 0) {
			Scene = 8;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 1) {
			Skill = 2;
		}
		break;

		//パチモン
	case 2:
		if (side == 0)DrawTriangle(420, 433, 420, 453, 435, 443, GetColor(50, 50, 50), TRUE);
		if (side == 1) {
			DrawTriangle(10, 433, 10, 453, 25, 443, GetColor(50, 50, 50), TRUE);
			SkillSelect = 2;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 0) {
			Scene = 9;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 1) {
			Skill = 3;
		}
		break;

		//にげる
	case 3:
		if (side == 0)DrawTriangle(540, 433, 540, 453, 555, 443, GetColor(50, 50, 50), TRUE);
		if (side == 1) {
			DrawTriangle(210, 433, 210, 453, 225, 443, GetColor(50, 50, 50), TRUE);
			SkillSelect = 3;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 0) {
			Scene = 10;
		}
		if (Key[KEY_INPUT_RETURN] == 1 && side == 1) {
			Skill = 4;
		}
		break;
	}
}

void CopyWrite() {
	SetFontSize(12);                             //文字サイズ変更
	SetFontThickness(10);                         //文字の太さ変更
	DrawFormatString(0, 0, GetColor(255, 255, 255), "(C) 2020 Tsuyoshi");
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//TRUE:ウィンドウモード、FALSE:フルスクリーンモード
	ChangeWindowMode(TRUE);

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1) {
		return -1;	//エラーが起きたら直ちに終了
	}

	//描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);


	//画像の描画(メモリに画像データを読み込む)
	//int x = 50;
	//int Handle;
	//Handle = LoadGraph("image_00.png");
	
	int Sentence = 0;
	int c = 0;
	int BlackCnt = 0;
	int image[12];
	int MapImage_1;
	int MapImage_2[5];
	int old_x, old_y;

	//画像の分割読み込み
	//LoadDivGraph("character_chip_1.png", 16, 4, 4, 32, 32, image);
	LoadDivGraph("./images/pipo-halloweenchara2016_26.png", 12, 3, 4, 32, 32, image);
	MapImage_1 = LoadGraph("./images/pipo-map001.png");
	//MapImage_2 = LoadGraph("pipo-map002.png"); 
	LoadDivGraph("./images/pipo-map001_at-mori.png", 5, 1, 5, 32, 32, MapImage_2);

	int MonImage_1[12];
	//パチモンAの読み込み
	LoadDivGraph("./images/pipo-halloweenchara2016_13.png", 12, 3, 4, 32, 32, MonImage_1);

	int MonImage_2[12];
	//パチモンBの読み込み
	LoadDivGraph("./images/pipo-halloweenchara2016_17.png", 12, 3, 4, 32, 32, MonImage_2);

	Pachimon pachi_A, pachi_B;
	pachi_A = { "パチモンA", 110, "ひのこ", 20, 20, "ほのお", "ウルトラパンチ", 30, 20, "かくとう", "こおりのパンチ", 40, 15, "こおり", "ミラクルパンチ", 50, 15, "でんき" };
	pachi_B = { "パチモンB", 110, "パンチ", 10, 20, "かくとう", "つよめのパンチ", 20, 20, "かくとう", "スーパーパンチ", 30, 15, "かくとう", "ウルトラパンチ", 40, 15, "かくとう" };

	int CurrentHP_A = pachi_A.HitPont;
	int CurrentHP_B = pachi_B.HitPont;

	int used_waza_pp_1 = 0;
	int used_waza_pp_2 = 0;
	int used_waza_pp_3 = 0;
	int used_waza_pp_4 = 0;

	int pachi_B_kakuritsu = 0;

	bool GameClearFlag = FALSE;

	//ウィンドウのxボタンで画面を閉じる
	while (1) {
		//ProcessMessage()→他のプログラムとうまく連絡をとってくれる関数
		//xボタンが押されると、ProcessMessage関数は0以外を返す
		if (ProcessMessage() != 0) {
			break;
		}
		if (gpUpdateKey() != 0) {
			break;
		}

		ClearDrawScreen();	//画面を消す

		switch (Scene) {
		case 0:

				CurrentHP_B = pachi_B.HitPont;

				old_x = x;
				old_y = y;

				int kakuritsu;

				SetDrawBright(255, 255, 255);

				//マップを表示
				for (int j = 0; j < MAP_HEIGHT; j++) {
					for (int i = 0; i < MAP_WIDTH; i++) {
						if (MapData_1[j][i] == 0) {
							//DrawBox(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), TRUE);
								//DrawRotaGraph(x * MAP_SIZE, y * MAP_SIZE, 1.0, 0.0, MapImage_1, TRUE);
							DrawGraph(i * MAP_SIZE, j * MAP_SIZE, MapImage_1, TRUE);
						}
						if (MapData_2[j][i] == 1) {
							DrawGraph(i * MAP_SIZE, j * MAP_SIZE, MapImage_2[0], TRUE);
						}
					}
				}

				if (!GameClearFlag) {

					gpCalc();

					gpCalc2();

					// ブロックの当たり判定
					if (old_x != x || old_y != y) {
						for (int j = 0; j < MAP_HEIGHT; j++)
						{
							for (int i = 0; i < MAP_WIDTH; i++)
							{
								if (MapData_2[j][i] == 1)
								{
									if (((x > i * MAP_SIZE && x < i * MAP_SIZE + MAP_SIZE - 10) || (i * MAP_SIZE > x && i * MAP_SIZE + 10 < x + 32)) &&
										((y > j * MAP_SIZE && y < j * MAP_SIZE + MAP_SIZE - 30) || (j * MAP_SIZE > y && j * MAP_SIZE + 10 < y + 32)))
									{
										// ブロックに当たった
										//DrawFormatString(0, 0, GetColor(255, 0, 0), "座標[%d,%d]", x, y);
										kakuritsu = GetRand(299);		//0～299の数のどれか
										if (kakuritsu == 299) {
											kakuritsu = 0;
											Scene = 1;
										}
									}
								}
							}
						}
					}
				}

				if (GameClearFlag) {
					DrawBox(0, 380, 640, 480, GetColor(0, 0, 0), TRUE);  //画面下に黒色の四角形を描画
					DrawBox(10, 390, 630, 470, GetColor(255, 255, 255), TRUE);		//吹き出し用の白い四角形
					SetFontSize(25);                             //文字サイズ変更
					SetFontThickness(20);                         //文字の太さ変更
					DrawFormatString(15, 402, GetColor(50, 50, 50), "ゲームクリア！ おめでとう！！");
					DrawFormatString(15, 432, GetColor(50, 50, 50), "画面右上のXボタンを押して終了");
				}

				DrawGraph(x, y, image[result], TRUE);
				//DrawGraph(200, 200, MapImage_1, TRUE);
				//DrawBox(200, 200, 232, 232, GetColor(255, 0, 0), TRUE);

				gpCalc3();



			break;


		case 1:
			if (c >= 0 && c < 256)             //cが0~256の時
				SetDrawBright(c, c, c);        //段々あかるく(c= 0->255)
			if (c >= 256 && c < 400)           //cが256~400の時
				SetDrawBright(255, 255, 255);  //通常の明るさ
			if (c >= 400 && c < 400 + 256)     //cが400~400+256の時
				SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));	//段々暗く(c= 255->0)

			//DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //画面全体に白い四角形を描画

			//マップを表示
			for (int j = 0; j < MAP_HEIGHT; j++) {
				for (int i = 0; i < MAP_WIDTH; i++) {
					if (MapData_1[j][i] == 0) {
						//DrawBox(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), TRUE);
							//DrawRotaGraph(x * MAP_SIZE, y * MAP_SIZE, 1.0, 0.0, MapImage_1, TRUE);
						DrawGraph(i * MAP_SIZE, j * MAP_SIZE, MapImage_1, TRUE);
					}
					if (MapData_2[j][i] == 1) {
						DrawGraph(i * MAP_SIZE, j * MAP_SIZE, MapImage_2[0], TRUE);
					}
				}
			}
			//DrawFormatString(0, 0, GetColor(255, 0, 0), "座標[%d,%d]", x, y);
			DrawGraph(x, y, image[result], TRUE);

			//c += 速度;                                  //cをカウントアップ
			c += 20;

			if (c >= 400 + 256) {
				c = 0;
				Scene = 1;
				BlackCnt++;
				if (BlackCnt == 3) {
					Scene = 2;
					BlackCnt = 0;

				}
			}

			break;


		case 2:
			c++;

			if (c > 120) {
				SetDrawBright(255, 255, 255);
			}

			if (c > 121) {
				DrawBox(0, 0, 640, 480, GetColor(0, 100, 255), TRUE);  //画面全体に水色の四角形を描画
				DrawBox(0, 480 - BlackCnt, 640, 480, GetColor(0, 0, 0), TRUE);  //画面下に黒色の四角形を描画
				BlackCnt += 2;

				if (BlackCnt > 100) {
					c = 0;
					BlackCnt = 0;
					Scene = 3;
					break;
				}
			}



			//DrawBox(0 * MAP_SIZE, 0 * MAP_SIZE, 0 * MAP_SIZE + MAP_SIZE, 0 * MAP_SIZE + MAP_SIZE, GetColor(255, 0, 0), TRUE);
			//DrawFormatString(0, 0, GetColor(255, 0, 0), "バトルシーン");
			break;


		case 3:
			c += 10;
			DrawBox(0, 0, 640, 480, GetColor(0, 100, 255), TRUE);  //画面全体に水色の四角形を描画

			if (c >= 0 && c <= 500) {
				DrawOval(c-5, 150, 130, 40, GetColor(0, 200, 0), TRUE);			//野生用の楕円
				DrawRotaGraph(c-5, 120, 3.0, 0.0, MonImage_2[4], TRUE);
				DrawOval(640 - c, 390, 220, 60, GetColor(0, 200, 0), TRUE);		//プレイヤー用の楕円
				DrawRotaGraph(600-c, 340, 4.0, 0.0, image[7], TRUE);
			}

			if (c <= 500)DrawBox(0, 380, 640, 480, GetColor(0, 0, 0), TRUE);  //画面下に黒色の四角形を描画

			if (c >= 0 && c < 256) {
				DrawBox(10, 390, 630, 470, GetColor(c, c, c), TRUE);  //吹き出し用の白い四角形を描画
			}

			if (c >= 256 && c <= 500) {
				DrawBox(10, 390, 630, 470, GetColor(255, 255, 255), TRUE);		//吹き出し用の白い四角形
			}

			if (c > 500) {
				DrawOval(500, 150, 130, 40, GetColor(0, 200, 0), TRUE);		//野生用の楕円
				DrawRotaGraph(495, 120, 3.0, 0.0, MonImage_2[4], TRUE);

				DrawOval(140, 390, 220, 60, GetColor(0, 200, 0), TRUE);		//プレイヤー用の楕円
				DrawRotaGraph(100, 340, 4.0, 0.0, image[7], TRUE);

				DrawBox(0, 380, 640, 480, GetColor(0, 0, 0), TRUE);  //画面下に黒色の四角形を描画
				DrawBox(10, 390, 630, 470, GetColor(255, 255, 255), TRUE);		//吹き出し用の白い四角形
				Scene = 4;
				c = 0;
			}

			//DrawFormatString(0, 0, GetColor(255, 0, 0), "バトルシーン");
			break;

		case 4:
			c++;
			DrawBattleArea(image[7], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			if (c >= 30) {
				c = 0;
				Scene = 5;
			}
			break;


		case 5:
			if (Key[KEY_INPUT_RETURN] == 1) {
				Sentence++;
				if (Sentence > 1)Sentence = 1;
			}

			switch (Sentence) {
				case 0:
					DrawBattleArea(image[7], MonImage_2[4]);
					DrawHP(CurrentHP_B);
					SetFontSize(25);                             //文字サイズ変更
					SetFontThickness(20);                         //文字の太さ変更
					DrawFormatString(15, 402, GetColor(50, 50, 50), "あ！ やせいの");
					DrawFormatString(15, 432, GetColor(50, 50, 50), "%sが とびだしてきた！ ▼", pachi_B.name);
					break;

				case 1:
					c++;
					if (0 < c && c <= 60) {
						DrawBattleArea(image[7], MonImage_2[4]);
						DrawHP(CurrentHP_B);
						SetFontSize(25);                             //文字サイズ変更
						SetFontThickness(20);                         //文字の太さ変更
						DrawFormatString(15, 402, GetColor(50, 50, 50), "ゆけっ！ %s！", pachi_A.name);
					}

					if (c > 60 && c <= 120) {
						DrawBattleArea(MonImage_1[11], MonImage_2[4]);
						DrawHP(CurrentHP_B);
						SetFontSize(25);                             //文字サイズ変更
						SetFontThickness(20);                         //文字の太さ変更
						DrawFormatString(15, 402, GetColor(50, 50, 50), "ゆけっ！ %s！", pachi_A.name);
					}

					if (c == 121) {
						DrawBattleArea(MonImage_1[11], MonImage_2[4]);
						DrawHP(CurrentHP_B);
						SetFontSize(25);                             //文字サイズ変更
						SetFontThickness(20);                         //文字の太さ変更
						DrawFormatString(15, 402, GetColor(50, 50, 50), "ゆけっ！ %s！", pachi_A.name);
						Sentence = 0;
						Scene = 6;
						c = 0;
					}
					break;
			}
			
			break;

		case 6:
			DrawBattleArea(MonImage_1[11], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			DrawHP_2(CurrentHP_A, pachi_A.HitPont);
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(15, 402, GetColor(50, 50, 50), "%sは どうする？", pachi_A.name);
			DrawBox(400, 370, 640, 480, GetColor(255, 255, 255), TRUE);		//メニュー用の白い四角形
			DrawBox(405, 375, 635, 475, GetColor(50, 50, 50), FALSE);
			SetFontSize(20);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(440, 398, GetColor(50, 50, 50), "たたかう");
			DrawFormatString(560, 398, GetColor(50, 50, 50), "バッグ");
			DrawFormatString(440, 433, GetColor(50, 50, 50), "パチモン");
			DrawFormatString(560, 433, GetColor(50, 50, 50), "にげる");

			DrawBattleKey(0);

			break;

		case 7:
			DrawBattleArea(MonImage_1[11], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			DrawHP_2(CurrentHP_A, pachi_A.HitPont);
			/*
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(15, 402, GetColor(50, 50, 50), "パチモンAは どうする？");
			
			*/

			switch (Skill) {
			case 0:
				DrawBox(0, 370, 640, 480, GetColor(255, 255, 255), TRUE);		//メニュー用の白い四角形

				DrawBox(5, 375, 395, 475, GetColor(50, 50, 50), FALSE);		//わざ選択枠
				DrawBox(405, 375, 635, 475, GetColor(50, 50, 50), FALSE);		//わざ説明用枠線

				SetFontSize(20);                             //文字サイズ変更
				SetFontThickness(20);                         //文字の太さ変更
				DrawFormatString(420, 398, GetColor(50, 50, 50), "PP");

				if (SkillSelect == 0) {
					DrawFormatString(535, 398, GetColor(50, 50, 50), "%d／%d", pachi_A.waza_pp_1 - used_waza_pp_1, pachi_A.waza_pp_1);
					DrawFormatString(415, 433, GetColor(50, 50, 50), "わざタイプ／%s", pachi_A.waza_type_1);
				}

				if (SkillSelect == 1) {
					DrawFormatString(535, 398, GetColor(50, 50, 50), "%d／%d", pachi_A.waza_pp_2 - used_waza_pp_2, pachi_A.waza_pp_2);
					DrawFormatString(415, 433, GetColor(50, 50, 50), "わざタイプ／%s", pachi_A.waza_type_2);
				}

				if (SkillSelect == 2) {
					DrawFormatString(535, 398, GetColor(50, 50, 50), "%d／%d", pachi_A.waza_pp_3 - used_waza_pp_3, pachi_A.waza_pp_3);
					DrawFormatString(415, 433, GetColor(50, 50, 50), "わざタイプ／%s", pachi_A.waza_type_3);
				}

				if (SkillSelect == 3) {
					DrawFormatString(535, 398, GetColor(50, 50, 50), "%d／%d", pachi_A.waza_pp_4 - used_waza_pp_4, pachi_A.waza_pp_4);
					DrawFormatString(415, 433, GetColor(50, 50, 50), "わざタイプ／%s", pachi_A.waza_type_4);
				}

				DrawFormatString(30, 398, GetColor(50, 50, 50), "%s", pachi_A.waza_1);
				DrawFormatString(230, 398, GetColor(50, 50, 50), "%s", pachi_A.waza_2);
				DrawFormatString(30, 433, GetColor(50, 50, 50), "%s", pachi_A.waza_3);
				DrawFormatString(230, 433, GetColor(50, 50, 50), "%s", pachi_A.waza_4);

				DrawBattleKey(1);
				break;
			case 1:
				c++;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "%sの", pachi_A.name);
				DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_A.waza_1);
				if (c == 1)used_waza_pp_1++;
				if (c >= 60) {
					if (c < pachi_A.waza_damage_1 + 60) {
						CurrentHP_B -= 1;
						if (CurrentHP_B < 0) {
							CurrentHP_B = 0;
						}
					}
				}
				if (c >= 240) {
					if (CurrentHP_B == 0)Skill = 6;
					else Skill = 5;
					c = 0;
					pachi_B_kakuritsu = GetRand(3);
					BattleKey = 0;
					BattleKeyX = 0;
					BattleKeyY = 0;
				}
				//Scene = 5;
				//DrawFormatString(0, 0, GetColor(50, 50, 50), "%d", CurrentHP_B);
				break;
			case 2:
				c++;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "%sの", pachi_A.name);
				DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_A.waza_2);
				if (c == 1)used_waza_pp_2++;
				if (c >= 60) {
					if (c < pachi_A.waza_damage_2 + 60) {
						CurrentHP_B -= 1;
						if (CurrentHP_B < 0) {
							CurrentHP_B = 0;
						}
					}
				}
				if (c >= 240) {
					if (CurrentHP_B == 0)Skill = 6;
					else Skill = 5;
					c = 0;
					pachi_B_kakuritsu = GetRand(3);
					BattleKey = 0;
					BattleKeyX = 0;
					BattleKeyY = 0;
				}
				break;
			case 3:
				c++;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "%sの", pachi_A.name);
				DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_A.waza_3);
				if (c == 1)used_waza_pp_3++;
				if (c >= 60) {
					if (c < pachi_A.waza_damage_3 + 60) {
						CurrentHP_B -= 1;
						if (CurrentHP_B < 0) {
							CurrentHP_B = 0;
						}
					}
				}
				if (c >= 240) {
					if (CurrentHP_B == 0)Skill = 6;
					else Skill = 5;
					c = 0;
					pachi_B_kakuritsu = GetRand(3);
					BattleKey = 0;
					BattleKeyX = 0;
					BattleKeyY = 0;
				}
				break;
			case 4:
				c++;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "%sの", pachi_A.name);
				DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_A.waza_4);
				if (c == 1)used_waza_pp_4++;
				if (c >= 60) {
					if (c < pachi_A.waza_damage_4 + 60) {
						CurrentHP_B -= 1;
						if (CurrentHP_B < 0) {
							CurrentHP_B = 0;
						}
					}
				}
				if (c >= 240) {
					if (CurrentHP_B == 0)Skill = 6;
					else Skill = 5;
					c = 0;
					pachi_B_kakuritsu = GetRand(3);
					BattleKey = 0;
					BattleKeyX = 0;
					BattleKeyY = 0;
				}
				break;

			case 5:
				c++;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "やせいの %sの", pachi_B.name);
				if (pachi_B_kakuritsu == 0) {
					DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_B.waza_1);
					if (c >= 60) {
						if (c < pachi_B.waza_damage_1 + 60) {
							CurrentHP_A -= 1;
							if (CurrentHP_A < 0) {
								CurrentHP_A = 0;
							}
						}
					}
				}
				if (pachi_B_kakuritsu == 1) {
					DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_B.waza_2);
					if (c >= 60) {
						if (c < pachi_B.waza_damage_2 + 60) {
							CurrentHP_A -= 1;
							if (CurrentHP_A < 0) {
								CurrentHP_A = 0;
							}
						}
					}
				}
				if (pachi_B_kakuritsu == 2) {
					DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_B.waza_3);
					if (c >= 60) {
						if (c < pachi_B.waza_damage_3 + 60) {
							CurrentHP_A -= 1;
							if (CurrentHP_A < 0) {
								CurrentHP_A = 0;
							}
						}
					}
				}
				if (pachi_B_kakuritsu == 3) {
					DrawFormatString(15, 432, GetColor(50, 50, 50), "%s！", pachi_B.waza_4);
					if (c >= 60) {
						if (c < pachi_B.waza_damage_4 + 60) {
							CurrentHP_A -= 1;
							if (CurrentHP_A < 0) {
								CurrentHP_A = 0;
							}
						}
					}
				}

				if (c >= 240) {
					c = 0;
					if (CurrentHP_A == 0)Skill = 6;
					else {
						Skill = 0;
						Scene = 6;
					}
				}
				break;

			case 6:
				if (CurrentHP_A == 0) {
					DrawFormatString(15, 402, GetColor(50, 50, 50), "きみの %sは たおれた！ ▼", pachi_A.name);
					if (Key[KEY_INPUT_RETURN] == 1) {
						Skill = 7;
					}
				}
				if (CurrentHP_B == 0) {
					DrawFormatString(15, 402, GetColor(50, 50, 50), "あいての %sは たおれた！ ▼", pachi_B.name);
					if (Key[KEY_INPUT_RETURN] == 1) {
						Skill = 10;
						GameClearFlag = TRUE;
					}
				}
				break;

			case 7:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "きみの てもちには");
				DrawFormatString(15, 432, GetColor(50, 50, 50), "たたかえる パチモンが いない！ ▼");
				if (Key[KEY_INPUT_RETURN] == 1) {
					Skill = 8;
				}
				break;

			case 8:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "…… …… ……");
				DrawFormatString(15, 432, GetColor(50, 50, 50), "…… …… …… ▼");
				if (Key[KEY_INPUT_RETURN] == 1) {
					Skill = 9;
				}
				break;

			case 9:
				c+=2;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "きみは");
				DrawFormatString(15, 432, GetColor(50, 50, 50), "めのまえが まっくらになった！");
				if (256 + 120 > c && c >= 120) {
					SetDrawBright(255 - (c - 120), 255 - (c - 120), 255 - (c - 120));
				}
				if (c > 256 + 120) {
					SetDrawBright(255, 255, 255);
					Scene = 11;
					Skill = 0;
					c = 0;
				}
				break;

			case 10:
				c += 2;
				DrawFormatString(15, 402, GetColor(50, 50, 50), "あいての %sは たおれた！ ▼", pachi_B.name);
				if (256 + 120 > c && c >= 120) {
					SetDrawBright(255 - (c - 120), 255 - (c - 120), 255 - (c - 120));
				}
				if (c > 256 + 120) {
					SetDrawBright(255, 255, 255);
					Scene = 0;
					Skill = 0;
					c = 0;
				}
				break;
			}

			break;

		case 8:
			DrawBattleArea(MonImage_1[11], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			DrawHP_2(CurrentHP_A, pachi_A.HitPont);
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			if (Key[KEY_INPUT_RETURN] == 1) {
				c++;
			}
			switch (c) {
			case 0:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "バッグには せいさくしゃからの");
				DrawFormatString(15, 432, GetColor(50, 50, 50), "てがみが はいっていた！ ▼");
				break;
			case 1:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "「このゲームを");
				DrawFormatString(15, 432, GetColor(50, 50, 50), "　あそんでくれて ありがとう！」 ▼");
				break;
			case 2:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "ほかには なにも はいっていないようだ… ▼");
				break;
			case 3:
				DrawFormatString(15, 402, GetColor(50, 50, 50), "ほかには なにも はいっていないようだ… ▼");
				c = 0;
				Scene = 6;
				break;
			}

			break;

		case 9:
			DrawBattleArea(MonImage_1[11], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			DrawHP_2(CurrentHP_A, pachi_A.HitPont);
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(15, 402, GetColor(50, 50, 50), "こうたいできるパチモンがいません！ ▼");
			if (Key[KEY_INPUT_RETURN] == 1) {
				Scene = 6;
			}

			break;

		case 10:
			c+=2;
			DrawBattleArea(MonImage_1[11], MonImage_2[4]);
			DrawHP(CurrentHP_B);
			DrawHP_2(CurrentHP_A, pachi_A.HitPont);
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(15, 402, GetColor(50, 50, 50), "うまくにげきれた！");
			if (256 + 60 > c && c >= 60) {
				SetDrawBright(256 + 60 - c, 256 + 60 - c, 256 + 60 - c);
			}
			if (256 + 60 < c) {
				c = 0;
				Scene = 0;
				BattleKey = 0;
				BattleKeyX = 0;
				BattleKeyY = 0;
			}

			break;

		case 11:
			SetFontSize(25);                             //文字サイズ変更
			SetFontThickness(20);                         //文字の太さ変更
			DrawFormatString(15, 402, GetColor(200, 0, 0), "Game Over...");
			DrawFormatString(15, 432, GetColor(200, 0, 0), "画面右上のXボタンを押して終了");
			break;

		}

		CopyWrite();
		ScreenFlip();	//裏画面を表画面に反映

	}

	//DXライブラリの終了処理
	DxLib_End();

	return 0;
}
