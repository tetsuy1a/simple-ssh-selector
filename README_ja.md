# Simple SSH Selector

![for Windows](https://img.shields.io/badge/for-Windows-blue)

`~/.ssh/config` の `Host` エントリを読み取り、一覧から選択して SSH 接続できるシンプルな TUI アプリケーションです。

## ⚙️ 特徴

- `Host` を自動抽出しリストアップ（複数指定にも対応）
- 矢印キーで接続先ホストを選択するだけ。 `ssh` コマンド入力の手間が省けます

## 💻 動作環境

- Windows 10 / 11
- OpenSSH（`ssh` コマンドが PATH に通っていること）

## 🛠️ ビルド

MinGW-w64でコンパイルできることを確認済み。

```bash
gcc ssh_selector.c -o ssh_selector.exe
```

シンプルなプログラムなので他のコンパイラでもビルド可能だと思います（未検証）。

## ▶️ 使い方

1. `C:\Users\<ユーザー名>\.ssh\config` を用意
2. ビルドした `ssh_selector.exe` を実行

```bash
ssh_selector.exe
```

### ⌨️ 操作

- ↑ / ↓ : ホスト選択
- Enter : SSH接続
- q : 終了

## 📄 対応している `config` 記述

- `Host web1`
- `Host web1 web2`

※ `Host *` やワイルドカードは無視します

## ⚠️ 既知の制限

- `Include` ディレクティブ未対応
- `HostName`, `User`, `Port` などの詳細情報は未表示
- ホスト数が非常に多い場合のスクロール未対応

## 📜 ライセンス

本ソフトウェアは MIT License のもとで提供されます。 詳細は同梱の `LICENSE` ファイルを参照してください。
