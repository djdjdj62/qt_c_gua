#include "play.h"
#include "ui_play.h"
#include "mainwindow.h"
//----------------

#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#define CLOCK_TIMEINTERVAL 1000	// 時間計時器間隔
#define OBJECT_TIMEINTERVAL 10	// 物體計時器間隔
#define GAME_TIME 30			// 遊戲時間
#define CAR_SPEED 2				// 車子移動速度(水平)
#define CAR_MOVE_SPEED 2		// 車子移動速度(垂直)
#define CAR_INIT_Y_POS 220		// 車子初始位置(垂直)
#define BLOCK01_X_POS 5200
#define BLOCK01_Y_POS 40
#define BLOCK02_X_POS 3100
#define BLOCK02_Y_POS 150
#define BLOCK03_X_POS 900
#define BLOCK03_Y_POS 190
#define BLOCK04_X_POS 2500
#define BLOCK04_Y_POS 40
#define BLOCK05_X_POS 1200
#define BLOCK05_Y_POS 510
#define BLOCK06_X_POS 2500
#define BLOCK06_Y_POS 380

#define BLOCK10_X_POS 500
#define BLOCK10_Y_POS 120
#define BLOCK11_X_POS 1500
#define BLOCK11_Y_POS 70
#define BLOCK12_X_POS 1800
#define BLOCK12_Y_POS 160
#define BLOCK13_X_POS 5700
#define BLOCK13_Y_POS 400
#define BLOCK14_X_POS 2500
#define BLOCK14_Y_POS 700
#define BLOCK15_X_POS 3000
#define BLOCK15_Y_POS 240

#define BLOCK16_X_POS 2100
#define BLOCK16_Y_POS 250
#define BLOCK17_X_POS 3600
#define BLOCK17_Y_POS 170
#define BLOCK18_X_POS 900
#define BLOCK18_Y_POS 400
#define BLOCK19_X_POS 5000
#define BLOCK19_Y_POS 160
#define BLOCK20_X_POS 2300
#define BLOCK20_Y_POS 400
#define BLOCK21_X_POS 1780
#define BLOCK21_Y_POS 340
#define BLOCK22_X_POS 4600
#define BLOCK22_Y_POS 180


/*
 * game_status:
 * 0 => init
 * 1 => playing
 * 2 => pause
 * 3 => timeout
 * 4 => die
 */

//-----------------------------------

play::play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);

    //------------------------------------
    game_status = 0;

    // hide block
    ui->block_01->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_02->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_03->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_04->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_05->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_06->setGeometry(QRect(-100, 0, 64, 64));


    // 移動物體
    bgm_pos = 0;
    object_timer = new QTimer(this);	// 建立計時器
    connect(object_timer, SIGNAL(timeout()), this, SLOT(update_object()));	// 連接訊號
    object_timer->start(OBJECT_TIMEINTERVAL);	// 每隔10毫秒更新一次

    // 更新時間
    time = GAME_TIME;
    clock_timer = new QTimer(this);	// 建立計時器
    connect(clock_timer, SIGNAL(timeout()), this, SLOT(update_time()));	// 連接訊號
    //clock_timer->start(CLOCK_TIMEINTERVAL);	// 每隔1000毫秒更新一次

    //-------------------------------------------
}

play::~play()
{
    delete ui;
}

void play::on_pushButton_clicked()
{
    MainWindow * main_window = new MainWindow();
    this->close();
    main_window->show();
    qDebug() << "返回主畫面!";
}


void play::update_time() {
    time -= 1;	// 時間每次減少1

    ui->lcd_clock->display(time);

    if(time == 0) {
        game_status = 3;	// 設為 timeout 的狀態
        game_stop();
    }
}

void play::game_stop() {
    clock_timer->stop();
    object_timer->stop();

    if(game_status == 3) {
        // timeout 時間到，過關
        ui->label_title->setPixmap(QPixmap(":/play_data/game_timeout.png"));	// 設定標題圖片
    } else if(game_status == 4) {
        // die 撞到障礙物，失敗
        ui->label_title->setPixmap(QPixmap(":/play_data/game_falied.png"));	// 設定標題圖片
    }
    ui->label_title->setVisible(true);	// 顯示標題圖片
    ui->button_start_game->setVisible(true);	// 顯示[開始遊戲]按鈕

    //ui->action_start_game->setText("開始遊戲");	// 設定選單[開始遊戲]按鈕的文字
}

void play::update_object() {
    bgm_pos -= 1 * CAR_SPEED;	// 背景位置每次往左移動1

    ui->background->setGeometry(QRect(bgm_pos, 0, 4800, 512));	// 設定背景位置
    if(bgm_pos == -32 * CAR_SPEED) {
        // 當移動一圈，背景從頭顯示
        bgm_pos = 0;
    }

    if(game_status == 1) {
        // playing

        car_distance += 1 * CAR_SPEED;	// 增加移動距離
        ui->label_distance->setText("行駛距離: " + QString::number(car_distance, 'f', 0) + "公尺");	// 顯示移動距離
        move_car();			// 呼叫 move_car() 移動車子的位置
        move_blocks();		// 呼叫 move_blocks() 移動障礙物
        detect_blocks();	// 呼叫 detect_blocks() 偵測障礙物
    }
}

void play::move_car() {
    int car_new_pos = car_pos + car_direction * CAR_MOVE_SPEED;	// 將接下來要移動到的位置暫存起來
    if((car_new_pos) >= 30 && (car_new_pos) <= 410) {			// 判斷接下來要移動的位置是否超過跑道上下邊緣
        // 未超過邊緣
        car_pos = car_new_pos;	// 變更車子的位置
        ui->car->setGeometry(QRect(10, car_pos, 137, 71));	// 設定車子的垂直位置
    } else {
        // 超過邊緣
        game_status = 4;	// 設為 die 的狀態
        game_stop();		// 遊戲結束
    }
}

void play::on_button_start_game_clicked() {
    game_start();
}

void play::game_start() {
    game_status = 1;							// 設為 playing 的狀態

    ui->label_title->setVisible(false);			// 隱藏遊戲標題
    ui->button_start_game->setVisible(false);	// 隱藏開始遊戲按鈕

    clock_timer->start(CLOCK_TIMEINTERVAL);		// 每隔1000毫秒更新一次

    time = GAME_TIME;							// 重設遊戲時間
    ui->lcd_clock->display(time);				// 顯示遊戲時間

    car_pos = CAR_INIT_Y_POS;					// 重設車子的垂直位置(位於中央)
    car_distance = 0;							// 重設移動距離
    car_direction = 0;							// 重設車子移動方向(垂直)

    bgm_pos = 0;								// 重設背景位置

    if(!object_timer->isActive()) {
        // 若物體移動計時器未啟動，則將它啟動
        object_timer->start(OBJECT_TIMEINTERVAL);
    }

    //ui->action_start_game->setText("暫停遊戲");	// 設定選單[開始遊戲]按鈕的文字
}

//void play::game_pause() {
//    if(game_status == 1) {
//        // playing 變為 pause
//        game_status = 2;		// 設為 pause 的狀態

//        clock_timer->stop();	// 停止時間計時器
//        object_timer->stop();	// 停止物體移動計時器
//        ui->label_title->setPixmap(QPixmap(":/play_data/game_pause.png"));	// 設定標題圖片
//        ui->label_title->setVisible(true);	// 顯示標題圖片
//        //ui->action_start_game->setText("開始遊戲");	// 設定選單[開始遊戲]按鈕的文字

//    } else if(game_status == 2) {
//        // pause 變為 playing
//        game_status = 1;		// 設為 playing 的狀態

//        clock_timer->start(CLOCK_TIMEINTERVAL);	// 開始時間計時器
//        object_timer->start(OBJECT_TIMEINTERVAL);	// 開始物體移動計時器
//        //ui->action_start_game->setText("暫停遊戲");	// 設定選單[開始遊戲]按鈕的文字
//        ui->label_title->setVisible(false);	// 顯示標題圖片
//    }
//}

void play::keyPressEvent(QKeyEvent *event) {
    switch (event->key()){
        case Qt::Key_Up:
            car_direction = -1;
            //qDebug() << "up";
            break;
        case Qt::Key_Down:
            car_direction = 1;
            //qDebug() << "down";
            break;
        case Qt::Key_Space:
            //game_pause();
            //qDebug() << "space";
            break;
    }
}

void play::move_blocks() {
    ui->block_01->setGeometry(QRect(BLOCK01_X_POS - car_distance, BLOCK01_Y_POS, 64, 64));
    ui->block_02->setGeometry(QRect(BLOCK02_X_POS - car_distance, BLOCK02_Y_POS, 64, 64));
    ui->block_03->setGeometry(QRect(BLOCK03_X_POS - car_distance, BLOCK03_Y_POS, 64, 64));
    ui->block_04->setGeometry(QRect(BLOCK04_X_POS - car_distance, BLOCK04_Y_POS, 64, 64));
    ui->block_05->setGeometry(QRect(BLOCK05_X_POS - car_distance, BLOCK05_Y_POS, 64, 64));
    ui->block_06->setGeometry(QRect(BLOCK06_X_POS - car_distance, BLOCK06_Y_POS, 64, 64));

    ui->block_10->setGeometry(QRect(BLOCK10_X_POS - car_distance, BLOCK10_Y_POS, 64, 64));
    ui->block_11->setGeometry(QRect(BLOCK11_X_POS - car_distance, BLOCK11_Y_POS, 64, 64));
    ui->block_12->setGeometry(QRect(BLOCK12_X_POS - car_distance, BLOCK12_Y_POS, 64, 64));
    ui->block_13->setGeometry(QRect(BLOCK13_X_POS - car_distance, BLOCK13_Y_POS, 64, 64));
    ui->block_14->setGeometry(QRect(BLOCK14_X_POS - car_distance, BLOCK14_Y_POS, 64, 64));
    ui->block_15->setGeometry(QRect(BLOCK15_X_POS - car_distance, BLOCK15_Y_POS, 64, 64));

    ui->block_16->setGeometry(QRect(BLOCK16_X_POS - car_distance, BLOCK16_Y_POS, 64, 64));
    ui->block_17->setGeometry(QRect(BLOCK17_X_POS - car_distance, BLOCK17_Y_POS, 64, 64));
    ui->block_18->setGeometry(QRect(BLOCK18_X_POS - car_distance, BLOCK18_Y_POS, 64, 64));
    ui->block_19->setGeometry(QRect(BLOCK19_X_POS - car_distance, BLOCK19_Y_POS, 64, 64));
    ui->block_20->setGeometry(QRect(BLOCK20_X_POS - car_distance, BLOCK20_Y_POS, 64, 64));
    ui->block_21->setGeometry(QRect(BLOCK21_X_POS - car_distance, BLOCK21_Y_POS, 64, 64));

    ui->block_22->setGeometry(QRect(BLOCK22_X_POS - car_distance, BLOCK22_Y_POS, 64, 64));
}

void play::detect_blocks() {
    int tmp_padding_x, tmp_padding_y;	// 障礙物與車子的距離

    tmp_padding_x = BLOCK01_X_POS - car_distance;
    tmp_padding_y = BLOCK01_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK02_X_POS - car_distance;
    tmp_padding_y = BLOCK02_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK03_X_POS - car_distance;
    tmp_padding_y = BLOCK03_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK04_X_POS - car_distance;
    tmp_padding_y = BLOCK04_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK05_X_POS - car_distance;
    tmp_padding_y = BLOCK05_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK06_X_POS - car_distance;
    tmp_padding_y = BLOCK06_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK10_X_POS - car_distance;
    tmp_padding_y = BLOCK10_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK11_X_POS - car_distance;
    tmp_padding_y = BLOCK11_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK12_X_POS - car_distance;
    tmp_padding_y = BLOCK12_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK13_X_POS - car_distance;
    tmp_padding_y = BLOCK13_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }


    tmp_padding_x = BLOCK14_X_POS - car_distance;
    tmp_padding_y = BLOCK14_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK15_X_POS - car_distance;
    tmp_padding_y = BLOCK15_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK16_X_POS - car_distance;
    tmp_padding_y = BLOCK16_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK17_X_POS - car_distance;
    tmp_padding_y = BLOCK17_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK18_X_POS - car_distance;
    tmp_padding_y = BLOCK18_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK19_X_POS - car_distance;
    tmp_padding_y = BLOCK19_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK20_X_POS - car_distance;
    tmp_padding_y = BLOCK20_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK21_X_POS - car_distance;
    tmp_padding_y = BLOCK21_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

    tmp_padding_x = BLOCK22_X_POS - car_distance;
    tmp_padding_y = BLOCK22_Y_POS - ui->car->y();
    if(is_collision(tmp_padding_x, tmp_padding_y)) {
        return;
    }

}

bool play::is_collision(int x, int y) {
    if((x < 147) && (x > -50)) {
        if((y < 55) && (y > -55)) {
            game_status = 4;	// 設為 die 的狀態
            game_stop();
            return true;
        }
    }
    return false;
}

//void play::on_action_start_game_triggered() {
//    switch (game_status) {
//        case 0:	// init
//        case 3:	// timeout
//        case 4:	// die
//            game_start();
//            break;
//        case 1:	// playing
//        case 2:	// pause
//            game_pause();
//            break;
//    }
//}

//void play::on_action_close_game_triggered() {
//    close();
//}
