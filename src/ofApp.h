#pragma once

#include "ofMain.h"
#define NUM 3

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        //外のフレーム変数
        float fx;
        float fy;
        float fw;
        float fh;

       //赤丸の変数
        float bx[NUM];
        float by[NUM];
        float radius[NUM];
        float bx_speed[NUM];
        float by_speed[NUM];
        int r[NUM],g[NUM],b[NUM];
        //パドルの変数
        float rx;   //パドルの中心のx座標
        float ry;   //パドルの中心のy座標
        float rw;   //パドルの幅
        float rh;   //パドルの高さ

        //障害壁の変数
        float wall_x;   //障害壁の中心のx座標
        float wall_y;   //障害壁の中心のy座標
        float wall_w;   //障害壁の幅
        float wall_h;   //障害壁の高さ
        float wall_speed;//障害壁の速度
        float wall_speed_flag;//障害壁の速度制限フラグ

        float x_shift;  //パドルのx移動速度
        float y_shift;  //パドルのy移動速度
        int padhit=0;   //パドル得点

        //ダメージの変数
        int damage_flag=0;//ダメージフラグ
        int damege_value=0;//ダメージの表示の長さ
        int damage_color_flag=0;//ダメージカラーフラグ

        //オプションスイッチの場所と大きさ
        float optbx;
        float optby;
        float optbh;
        float optbw;
        /*オプションスイッチ画面切り替え
         * 1ならオプション画面表示
         * 0なら非表示
         */
        int optSwich=0;

        //スピードオプションスイッチの場所と大きさ
        float optbsx;
        float optbsy;
        float optbsh;
        float optbsw;

        //球の大きさオプションスイッチの場所と大きさ
        float optbsizex;
        float optbsizey;
        float optbsizeh;
        float optbsizew;
        //verdanaフォントインスタンス
        ofTrueTypeFont verdana;

        //ボタンとマウスクリックの判定
        //Y軸
        bool btn_y(float OverY,float UnderY,float MouseY){
            if(OverY<=MouseY && UnderY>=MouseY){
                return true;
            }
            return false;
        }
        //X軸
        bool btn_x(float LeftX, float RightX,float MouseX){
            if(LeftX <=MouseX && RightX >= MouseX){
                return true;
            }
            return false;
        }

};
