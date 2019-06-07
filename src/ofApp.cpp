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

    //描画図形の初期値設定
    for(int i=0;i<NUM;i++){//円の個数回繰り返す
        bx[i] = ofGetWidth()/2.0;//急の描画位置x座標
        by[i] = ofGetHeight()/2.0;
        radius[i]=ofRandom(10,50);

        bx_speed[i]=ofRandom(2,15);
        by_speed[i]=ofRandom(5,15);
        r[i]=ofRandom(0,255);
        g[i]=ofRandom(0,255);
        b[i]=ofRandom(0,255);
    }
//    //赤丸の変数
//    bx=300;
//    by=300;
//    bx_speed=8;
//    by_speed=2;
//    radius=30;
    //パドルの変数
    rx = ofGetWidth()/2;  //パドルの初期位置　x座標
    ry = ofGetWidth()/2+ofGetHeight()/6; //パドルの初期位置　y座標
    rw = 100;   //パドルの幅
    rh = 10;    //パドルの高さ
    x_shift = 50;   //パドルのx移動速度
    y_shift = 50;   //パドルのy移動速度

    //障害壁の変数
    wall_x = ofGetWidth()/2;   //障害壁の中心のx座標
    wall_y = ofGetHeight()/5;   //障害壁の中心のy座標
    wall_w =rw;   //障害壁の幅
    wall_h =rh; //障害壁の高さ
    wall_speed=1;//障害壁のスピード

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
    for(int i=0;i<NUM;i++){//描画する円の個数回繰り返す
        bx[i] += bx_speed[i];	//x軸方向の移動
        by[i] += by_speed[i];	//y軸方向の移動

        //枠内で制限
        //x軸方向の範囲制限
        if ((bx[i]<fx-fw/2+radius[i])||
                          (bx[i]>fx+fw/2-radius[i])){
            bx_speed[i] *= -1;		//y軸方向の移動方向反転
        }
        //y軸方向の範囲制限
        if ((by[i]<fy-fh/2+radius[i])||
                          (by[i]>fy+fh/2-radius[i])){
            by_speed[i] *= -1;		//y軸方向の移動方向反転
        }

        //ダメージが０以下にならない
        if(by[i]>fy+fh/2-radius[i]){//
            if(padhit>0){
                padhit--;
            }else{
                damage_flag=1;
            }

        }
        //ダメージ効果の変数制御
        if(damage_flag==1){
            damege_value++;
        }
        if(damege_value>=80){
            damage_flag=0;
            damege_value=0;
        }
    }


//    //枠内で制限
//    //x軸方向の範囲制限
//    if ((bx[i]<fx-fw/2+radius[i])||
//                      (bx>fx+fw/2-radius[i])){
//        bx_speed[i] *= -1;		//y軸方向の移動方向反転
//    }
//    //y軸方向の範囲制限
//    if ((by<fy-fh/2+radius[i])||
//                      (by>fy+fh/2-radius[i])){
//        by_speed[i] *= -1;		//y軸方向の移動方向反転
//    }

    int padundr_y=ry+rh/2;//パドルの下のy座標
    int padover_y=ry-rh/2;//パドルの上のy座標
    int padleft_x=rx-rw/2;//パドルの左のx座標
    int padright_x=rx+rw/2;//パドルの右のx座標

    for(int i=0;i<NUM;i++){
        if((((padover_y<by[i]+radius[i])&&(padundr_y>by[i]+radius[i]))&&((padleft_x<bx[i]+radius[i])&&(padright_x>bx[i]-radius[i])))//パドルの上に球があたったとき
               || (((padover_y<by[i]-radius[i])&&(padundr_y>by[i]-radius[i]))&&((padleft_x<bx[i]+radius[i])&&(padright_x>bx[i]-radius[i])))//パドルの下に球があたったとき
                ){
            by_speed[i] *= -1;
            padhit++;
        }else{
            if(((by[i]-radius[i]<=ry) && (by[i]+radius[i]>=ry))){//球の側面の上のyとしたのyの間にパドルの中心のy軸の中に入ったとき （球の側面の上のy <= パドルの中心のy軸 <=球の側面ののy）
                if(((bx[i]+radius[i] >= padleft_x)&& (bx[i]+radius[i] <= padleft_x+rw/3)&& (bx_speed[i])>0)){//パドル左の処理
                    by_speed[i] *= -1;
                    bx_speed[i] *= -1;
                    padhit++;
                }
                if(((bx[i]-radius[i] <= padright_x)&& (bx[i]-radius[i] >= padright_x-rw/3))&& (bx_speed[i])<0){//パドル右の処理
                    by_speed[i] *= -1;
                    bx_speed[i] *= -1;
                    padhit++;
                }
            }
        }

    }

    //障害壁
    int wallundr_y=wall_y+wall_h/2;//パドルの下のy座標
    int wallover_y=wall_y-wall_h/2;//パドルの上のy座標
    int wallleft_x=wall_x-wall_w/2;//パドルの左のx座標
    int wallright_x=wall_x+wall_w/2;//パドルの右のx座標

    for(int i=0;i<NUM;i++){
        if((((wallover_y<by[i]+radius[i])&&(wallundr_y>by[i]+radius[i]))&&((wallleft_x<bx[i]+radius[i])&&(wallright_x>bx[i]-radius[i])))//パドルの上に球があたったとき
               || (((wallover_y<by[i]-radius[i])&&(wallundr_y>by[i]-radius[i]))&&((wallleft_x<bx[i]+radius[i])&&(wallright_x>bx[i]-radius[i])))//パドルの下に球があたったとき
                ){
            by_speed[i] *= -1;
            padhit++;
        }else{
            if(((by[i]-radius[i]<=ry) && (by[i]+radius[i]>=ry))){//球の側面の上のyとしたのyの間にパドルの中心のy軸の中に入ったとき （球の側面の上のy <= パドルの中心のy軸 <=球の側面ののy）
                if(((bx[i]+radius[i] >= wallleft_x)&& (bx[i]+radius[i] <= wallleft_x+rw/3)&& (bx_speed[i])>0)){//パドル左の処理
                    by_speed[i] *= -1;
                    bx_speed[i] *= -1;
                    padhit++;
                }
                if(((bx[i]-radius[i] <= wallright_x)&& (bx[i]-radius[i] >= wallright_x-rw/3))&& (bx_speed[i])<0){//パドル右の処理
                    by_speed[i] *= -1;
                    bx_speed[i] *= -1;
                    padhit++;
                }
            }
        }
    }

    //パドル制限
    //パドルの移動処理
    //x軸方向の移動範囲制限
   if (rx < 0+rw/2) {           //左端の制限
       rx = 0+rw/2;
   }

   if (rx > ofGetWidth()-rw/2){ //右端の制限
       rx = ofGetWidth()-rw/2;
   }

   //障害壁の移動
   if(wall_speed_flag==1){//フラグによってスピードの向きを変える
       wall_x += wall_speed;
   }else wall_x -= wall_speed;

   if (wall_x < 0+wall_w/2) {           //左端の制限
       wall_speed_flag=1;
   }

   if (wall_x > ofGetWidth()-wall_w/2){ //右端の制限
       wall_speed_flag=0;
   }


//   //オプションボタン
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ダメージ描画
    if(damage_flag==1){
        if(damage_color_flag==0){
            ofBackground(255,0,0);
            damage_color_flag=1;

        }else{
            ofBackground(0,153,0);
            damage_color_flag=0;
        }
    }else ofBackground(0,0,0);

    //枠の描画
    ofNoFill();						//塗り潰しなし
    ofSetLineWidth(4);				//線の太さを4
    ofSetColor(255, 255, 255);	//白色
    ofDrawRectangle(fx, fy, fw, fh);

    //障害壁の描画
    ofSetColor(255, 255, 0); //描画色　白
    ofRect(wall_x, wall_y, wall_w, wall_h);    //障害壁の描画

    //パドルの描画
    ofSetColor(255, 255, 255); //描画色　白
    ofRect(rx, ry, rw, rh);    //パドルの描画
    //円お描画
    ofFill();
    for (int i=0; i<NUM; i++) {
        ofSetColor(r[i], g[i], b[i]);			//描画色
        ofDrawCircle(bx[i], by[i], radius[i]);	//円の描画
    }


//    //円の描画
//    ofFill();                       //塗り潰しあり
//    ofSetColor(255, 0, 0);			//赤色
//    ofDrawCircle(bx, by, radius);	//円の描画
//    ofSetColor(30, 200, 200); // 文字色を指定


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
        sprintf(bx_speedStr, "Ball x speed: %.0f", abs(bx_speed[0]));
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
        sprintf(by_speedStr, "Ball y speed: %.0f", abs(by_speed[0]));
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
        sprintf(bx_sizeStr, "Ball size: %.0f", radius[0]);
        verdana.drawString(bx_sizeStr, optbsizex-60, optbsizey-50); // 文字とポジションを指定して描画

        ofSetColor(255, 255, 255);
        ofDrawRectangle(optbsizex, optbsizey, optbsizew*2, optbsizeh);
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Left click to low\nRight click to high", optbsizex-50, optbsizey); // 文字とポジションを指定して描画
    }
    if(optSwich==0){
        ofSetColor(0, 0, 0); // 文字色を指定
        verdana.drawString("Option OFF", optbx-50, optby);
        ofSetColor(255, 255, 255); // 文字色を指定
        char hit_Str[20];
        sprintf(hit_Str, "HIT\n%d", padhit);
        verdana.drawString(hit_Str, 500, 500);
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
        for(int i=0;i<NUM;i++){
            //球のx軸のスピードをｔ調整する
            float bx_speed_Sign = bx_speed[i]/abs(bx_speed[i]);
            if(button==0 && bx_speed[i]>1){//
                bx_speed[i]=((abs(bx_speed[i]))-1)*bx_speed_Sign;
            }else if(button==2)
                bx_speed[i]=(abs(bx_speed[i])+1)*bx_speed_Sign;
        }
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
    	for(int i=0;i<NUM;i++){
            float by_speed_Sign=by_speed[i]/abs(by_speed[i]);
            if(button==0 && by_speed[i]>1){
                by_speed[i]=((abs(by_speed[i]))-1)*by_speed_Sign;
            }else if(button==2)
                by_speed[i]=(abs(by_speed[i])+1)*by_speed_Sign;
    	}
    }

    /*
     * 級のサイズオプション
     */
    int optbsizeu_y=optbsizey+optbsizeh/2;//オプションボタンの下のy座標
    int optbsizeo_y=optbsizey-optbsizeh/2;//オプションボタンの上のy座標
    int optbsizel_x=optbsizex-optbsizew*2/2;//オプションボタンの左のx座標
    int optbsizer_x=optbsizex+optbsizew*2/2;//オプションボタンの右のx座標
    if(btn_y(optbsizeo_y,optbsizeu_y,y) && btn_x(optbsizel_x,optbsizer_x,x)&& optSwich==1){//ボタンとカーソルの位置が重なる && マウスクリックが左クリック
        for(int i=0;i<NUM;i++){
            //球のx軸のスピードをｔ調整する
            if(button==0 && radius[i]>1){//
                radius[i]--;
            }else if(button==2)
                radius[i]++;
        }
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
