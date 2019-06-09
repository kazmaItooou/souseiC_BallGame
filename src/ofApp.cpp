#include "ofApp.h"
#include <math.h>
#include <cmath>
#include <stdio.h>
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetCircleResolution(64);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetFrameRate(60);
    fx= ofGetWidth()/2.0;
    fy= ofGetHeight()/2.0;
    fw=870;
    fh=570;

    //赤丸の変数
    bx=300;
    by=300;
    bx_speed=8;
    by_speed=2;
    radius=30;
    //パドルの変数
    rx = ofGetWidth()/2;  //パドルの初期位置　x座標
    ry = ofGetHeight()/2; //パドルの初期位置　y座標
    rw = 100;   //パドルの幅
    rh = 10;    //パドルの高さ
    x_shift = 50;   //パドルのx移動速度
    y_shift = 50;   //パドルのy移動速度

    //オプションスイッチボタンの変数
    optbx=ofGetWidth()/2.0;
    optby=ofGetHeight()/2.0-fh/2-50;
    optbh=40;
    optbw=120;
    optSwich=0;

    //スピードオプションスイッチの場所と大きさ
    optbsx=ofGetWidth()/2.0/2.0;
    optbsy=ofGetHeight()/2.0;
    optbsh=40;
    optbsw=120;

    //球の大きさオプションスイッチの場所と大きさ
    optbsizex=ofGetWidth()/2.0/2.0;
    optbsizey=ofGetHeight()/2.0+150;
    optbsizeh=40;
    optbsizew=120;

    // Fonts
    ofTrueTypeFontSettings settings("verdana.ttf",12);//設定一式を納めるインスタンス
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);//日本語
    verdana.load(settings); // 設定をロード

}

//--------------------------------------------------------------
void ofApp::update(){
    //赤丸の移動処理
    bx += bx_speed;			//x軸方向の移動
    by += by_speed;			//y軸方向の移動
    //枠内で制限
    //x軸方向の範囲制限
    if ((bx<fx-fw/2+radius)||
                      (bx>fx+fw/2-radius)){
        bx_speed *= -1;		//y軸方向の移動方向反転
    }
    //y軸方向の範囲制限
    if ((by<fy-fh/2+radius)||
                      (by>fy+fh/2-radius)){
        by_speed *= -1;		//y軸方向の移動方向反転
    }

    //パドル制限sin,cos
    //暇があったらsin,cosで治す
    int padundr_y=ry+rh/2;//パドルの下のy座標
    int padover_y=ry-rh/2;//パドルの上のy座標
    int padleft_x=rx-rw/2;//パドルの左のx座標
    int padright_x=rx+rw/2;//パドルの右のx座標

    //パドル制限

//    if(((padleft_x<bx+radius)&&(padright_x>bx-radius))){

//        if( ((padover_y<by+radius)&&(padundr_y>by+radius)) ||
//            ((padover_y<by-radius)&&(padundr_y>by-radius))){

//        }
//    }

    if((((padover_y<by+radius)&&(padundr_y>by+radius))&&((padleft_x<bx+radius)&&(padright_x>bx-radius)))//パドルの上に球があたったとき
           || (((padover_y<by-radius)&&(padundr_y>by-radius))&&((padleft_x<bx+radius)&&(padright_x>bx-radius)))//パドルの下に球があたったとき
            ){
        by_speed *= -1;



//--------------------------------------------------
//パドルの横の当たり判定
    }else{
        if(((by-radius<=ry) && (by+radius>=ry))){//球の側面の上のyとしたのyの間にパドルの中心のy軸の中に入ったとき （球の側面の上のy <= パドルの中心のy軸 <=球の側面ののy）
            if(((bx+radius >= padleft_x)&& (bx+radius <= padleft_x+rw/3)&& (bx_speed)>0)){//パドル左の処理
            //if(球の右のx >= パドルの左のx) && (球の左のx <= パドルの左のx+余分検知)　&& Ballのスピード>0)
            if((bx+radius >= padleft_x)&& (bx+radius <= padleft_x+rw/3)&& (bx_speed)>0){//パドル左の処理
                by_speed *= -1;
                bx_speed *= -1;
            }
            if(((bx-radius <= padright_x)&& (bx-radius >= padright_x-rw/3))&& (bx_speed)<0){//パドル右の処理
            //if(球の左のx >= パドルの右のx) && (球の右のx <= パドルの右のx+余分検知)　&& Ballのスピード<0)
            if((bx-radius <= padright_x)&& (bx-radius >= padright_x-rw/3)&& (bx_speed)<0){//パドル右の処理
                by_speed *= -1;
                bx_speed *= -1;
            }
        }
    }
//--------------------------------------------------
    //パドルの移動処理
    //x軸方向の移動範囲制限
   if (rx < 0+rw/2) {           //左端の制限
       rx = 0+rw/2;
   }

   if (rx > ofGetWidth()-rw/2){ //右端の制限
       rx = ofGetWidth()-rw/2;
   }

//   //オプションボタン
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    //枠の描画
    ofNoFill();						//塗り潰しなし
    ofSetLineWidth(4);				//線の太さを4
    ofSetColor(255, 255, 255);	//白色
    ofDrawRectangle(fx, fy, fw, fh);

    //パドルの描画
    ofSetColor(255, 255, 255); //描画色　白
    ofRect(rx, ry, rw, rh);    //パドルの描画

    //円の描画
    ofFill();                       //塗り潰しあり
    ofSetColor(255, 0, 0);			//赤色
    ofDrawCircle(bx, by, radius);	//円の描画
    ofSetColor(30, 200, 200); // 文字色を指定

    //円の当たり判定
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofSetColor(0, 255, 0);
    ofDrawRectangle (bx ,by , radius*2 ,radius*2 );


    //オプションスイッチボタン切り替えの描画
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawRectangle(optbx, optby, optbw, optbh);
    if(optSwich==1){//オプションスイッチ表示制御が１なら
        ofSetColor(30, 200, 200); // 文字色を指定
        verdana.drawString("Option ON", optbx-40, optby); // 文字とポジションを指定して描画


        /*
         * スピードオプションx
         */
        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsx, optbsy-50, optbsw*2, optbsh);
        ofSetColor(0, 0, 0); // 文字色を指定
        char bx_speedStr[10];
        sprintf(bx_speedStr, "Ball x speed: %.0f", abs(bx_speed));
        verdana.drawString(bx_speedStr, optbsx-60, optbsy-50); // 文字とポジションを指定して描画

        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsx, optbsy, optbsw*2, optbsh);
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Left click to low\nRight click to high", optbsx-50, optbsy); // 文字とポジションを指定して描画


        /*
         * スピードオプションy
         */
        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsx, optbsy/2.0-50, optbsw*2, optbsh);
        ofSetColor(0, 0, 0); // 文字色を指定
        char by_speedStr[10];
        sprintf(by_speedStr, "Ball y speed: %.0f", abs(by_speed));
        verdana.drawString(by_speedStr, optbsx-60, optbsy/2.0-50); // 文字とポジションを指定して描画

        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsx, optbsy/2.0, optbsw*2, optbsh);
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Left click to low\nRight click to high", optbsx-50, optbsy/2.0); // 文字とポジションを指定して描画

        /*
         * Ballサイズオプション
         */
        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsizex, optbsizey-50, optbsizew*2, optbsizeh);
        ofSetColor(0, 0, 0); // 文字色を指定
        char bx_sizeStr[20];
        sprintf(bx_sizeStr, "Ball size: %.0f", radius);
        verdana.drawString(bx_sizeStr, optbsizex-60, optbsizey-50); // 文字とポジションを指定して描画

        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsizex, optbsizey, optbsizew*2, optbsizeh);
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Left click to low\nRight click to high", optbsizex-50, optbsizey); // 文字とポジションを指定して描画
    }
    if(optSwich==0){
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Option OFF", optbx-50, optby);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //左矢印キー
  if (key == OF_KEY_LEFT) {
        rx -= x_shift;
    }
    //右矢印キー
  if (key == OF_KEY_RIGHT) {
        rx += x_shift;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //オプションスイッチボタン
    int optbu_y=optby+optbh/2;//オプションボタンの下のy座標
    int optbo_y=optby-optbh/2;//オプションボタンの上のy座標
    int optbl_x=optbx-optbw/2;//オプションボタンの左のx座標
    int optbr_x=optbx+optbw/2;//オプションボタンの右のx座標

    if(btn_y(optbo_y,optbu_y,y) && btn_x(optbl_x,optbr_x,x)&& button==0){//ボタンとカーソルの位置が重なる && マウスクリックが左クリック
        //制御変数切り替え
        if(optSwich==1){
            optSwich=0;
        }else if(optSwich==0)
            optSwich=1;
    }


    /*
     * スピードオプションx
     */
    int optbsxu_y=optbsy+optbsh/2;//オプションボタンの下のy座標
    int optbsxo_y=optbsy-optbsh/2;//オプションボタンの上のy座標
    int optbsxl_x=optbsx-optbsw*2/2;//オプションボタンの左のx座標
    int optbsxr_x=optbsx+optbsw*2/2;//オプションボタンの右のx座標
    if(btn_y(optbsxo_y,optbsxu_y,y) && btn_x(optbsxl_x,optbsxr_x,x)&& optSwich==1){//ボタンとカーソルの位置が重なる && マウスクリックが左クリック

        //球のx軸のスピードをｔ調整する
        float bx_speed_Sign = bx_speed/abs(bx_speed);
        if(button==0 && bx_speed>1){//
            bx_speed=((abs(bx_speed))-1)*bx_speed_Sign;
        }else if(button==2)
            bx_speed=(abs(bx_speed)+1)*bx_speed_Sign;
    }


    /*
     * スピードオプションy
     */
    int optbsyu_y=optbsy/2.0+optbsh/2;//オプションボタンの下のy座標
    int optbsyo_y=optbsy/2.0-optbsh/2;//オプションボタンの上のy座標
    int optbsyl_x=optbsx-optbsw*2/2;//オプションボタンの左のx座標
    int optbsyr_x=optbsx+optbsw*2/2;//オプションボタンの右のx座標
    if(btn_y(optbsyo_y,optbsyu_y,y) && btn_x(optbsyl_x,optbsyr_x,x)&& optSwich==1){//ボタンとカーソルの位置が重なる && マウスクリックが左クリック
        //球の軸のスピードをｔ調整する
        float by_speed_Sign=by_speed/abs(by_speed);
        if(button==0 && by_speed>1){
            by_speed=((abs(by_speed))-1)*by_speed_Sign;
        }else if(button==2)
            by_speed=(abs(by_speed)+1)*by_speed_Sign;
    }

    /*
     * 級のサイズオプション
     */
    int optbsizeu_y=optbsizey+optbsizeh/2;//オプションボタンの下のy座標
    int optbsizeo_y=optbsizey-optbsizeh/2;//オプションボタンの上のy座標
    int optbsizel_x=optbsizex-optbsizew*2/2;//オプションボタンの左のx座標
    int optbsizer_x=optbsizex+optbsizew*2/2;//オプションボタンの右のx座標
    if(btn_y(optbsizeo_y,optbsizeu_y,y) && btn_x(optbsizel_x,optbsizer_x,x)&& optSwich==1){//ボタンとカーソルの位置が重なる && マウスクリックが左クリック

        //球のx軸のスピードをｔ調整する
        if(button==0 && radius>1){//
            radius--;
        }else if(button==2)
            radius++;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
