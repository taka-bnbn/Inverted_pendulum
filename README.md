## 倒立振子を無線で操作する．記録用のレポジトリ

このレポジトリは2年生前期に行われた，設計製作論3で行ったプログラムを保存する目的で作られたレポジトリである．


テーマ名 ESP32 を基板と接続し，スマホから操作をできるようにする

背景・目的

ESP32 を用いて無線通信を確立し，機体を操作できるようにする．
Arduino 系のマイコンを使うのは初めてだったので，環境構築から始めなければ
ならなかった．
バージョンによって使えないライブラリがあるなど問題がたくさんあった．バ
ージョンの組み合わせによる整合性など調べても分からないところは一つずつ
組み合わせないといけないなど，かなり時間を使ってしまう要因となった．

内容

1. 無線で接続する方法を考え,部品の調達をする．
当初,Bluetooth でデバイスと機体をシリアル通信しようとしていた．
なので，無線機能を備えていて，技適を取得済みでありなるべく安価である
という条件で部品を探した．
また，ESP32 とメイン基板に接続するために，ブレッドボードとジャンパ線
を用いることにした．

2. 機体に ESP32 を接続する．
ジャンパ線を用いて，ESP32 とメイン基板を接続した．
機体に設置されている eneloop から電源供給できるようにした．

3. ESP32 にプログラムや HTML を書き込む
デバイスと ESP32 自体を接続するプログラムとデバイスに表示する HTML を
ESP32 に書き込んだ．

4. 班員の要望に合わせて，無線通信や操作画面のボタンを増やすなどの調整を
する．
班員ごとに制御の安定性が異なっていたのと，操作するデバイスの OS によ
って操作する方法が違うほうが良いと結論づけられたため，ボタンを増やし
たり，減らしたりなど主に UI の調整を行った．

結果

1. 無線で接続する方法を考え,部品の調達をする．
調達自体は難なく進めることができたが，安いものを選んでしまったことが
要因で余計に事件を使ってしまうことになった．（3 に記述する）
ジャンパ線とブレッドボードを選んだ理由は付け外しが容易であり，はんだ
付けなどの作業も必要でないからである．
今回秋月電子通商にも部品を見に行ったが，Amazon のほうが安かったので，
Amazon で購入した．（図１）
<div align="center">
<img width="300" alt= "Image" src="https://github.com/user-attachments/assets/461da24e-52ea-4638-9eb6-d1403a9e3b44" />
</div>

図１：Amazon で購入


2. 機体に ESP32 を接続する．
ハードウエアはプラグラム上で出力されるピンと実際のピンを間違えない
ように接続した．
私が考えた方法では GPIO の数でしか操作する方法を増やせないものだった
が，やりようによっては GPIO の数以上に操作するバリエーションを増やせ
ると考えている．

3. ESP32 にプログラムや HTML を書き込む
今回はデバイスに表示させる操作画面に装飾をしたわけではないので，
HTML,CSS を書くのに時間はかからなかった．
しかしながら，デバイスと ESP32 を Bluetooth で接続することは諦めざるを
えなかった．
その理由は，最初に実験をするために購入した ESP32 の内一つの基板が恐ら
く不良品で，Bluetooth 通信をすることができなかった．
幸いなことに Wi-Fi 通信の機能は使えたので，今回は Wi-Fi で通信すること
にした．（図２）
<div align="center">
<img width="617" alt="Image" src="https://github.com/user-attachments/assets/c1bae3cb-ee56-484b-a455-e32edd549ab8" />
</div>

図２：通信の実験をしている様子


4. 班員の要望に合わせて，無線通信や操作画面のボタンを増やすなどの調整を
する．
当初は全員スマートフォンで操作しようと計画していたが，iOS から通信を
使用しようとすると遅延が大きく，Android OS の人のみがスマホで通信し，
iOS を使っている人は Windows から操作するという方針に落ち着いた．

考察
今回の研究で一番時間がかかった要因は，初期不良のパーツに気付かずに自分
のプログラムや環境がおかしいと思い込んでしまっていたことだ．
部品の選定時点で信頼できる出品者なのかなど調べることで，計画の大幅な遅
れなどは回避できたと考える．そのため，多少値が張っても信頼できる部品を調
達することが大切だと感じた．
