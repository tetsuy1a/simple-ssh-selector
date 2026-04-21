#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MAX_HOSTS 256
#define MAX_NAME 256

char hosts[MAX_HOSTS][MAX_NAME];
int host_count = 0;

HANDLE hConsole;
CONSOLE_CURSOR_INFO originalCursorInfo; // 保存用
WORD defaultAttr; // 元の色

/* カーソル移動 */
void move_cursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, coord);
}

/* カーソル表示切替 */
void set_cursor_visible(BOOL visible) {
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    info.bVisible = visible;
    SetConsoleCursorInfo(hConsole, &info);
}

/* 色設定 */
void set_color(WORD attr) {
    SetConsoleTextAttribute(hConsole, attr);
}

/* .ssh/config 読み込み */
void load_ssh_config() {
    char path[MAX_PATH];
    char *home = getenv("USERPROFILE");

    snprintf(path, sizeof(path), "%s\\.ssh\\config", home);

    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("Could not open %s\n", path);
        exit(1);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Host ", 5) == 0) {
            char *token = strtok(line + 5, " \t\r\n");
            while (token) {
                if (strcmp(token, "*") != 0 && token[0] != '?') {
                    strncpy(hosts[host_count], token, MAX_NAME - 1);
                    hosts[host_count][MAX_NAME - 1] = '\0';
                    host_count++;
                }
                token = strtok(NULL, " \t\r\n");
            }
        }
    }

    fclose(fp);
}

/* メニュー描画（反転表示） */
void draw_menu(int selected) {
    move_cursor(0, 0);

    printf("SSH Host Selector\n");
    printf("-----------------\n");
    printf("Up/Down: Move  Enter: Connect  q: Quit\n\n");

    for (int i = 0; i < host_count; i++) {
        if (i == selected) {
            // 反転（背景と文字色を入れ替え風にする）
            set_color(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
            printf("  %-50s\n", hosts[i]);
            set_color(defaultAttr);
        } else {
            printf("  %-50s\n", hosts[i]);
        }
    }
}

/* SSH実行 */
void connect_host(const char *host) {
    // SSH実行前にカーソルを元に戻す
    SetConsoleCursorInfo(hConsole, &originalCursorInfo);

    system("cls");
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ssh %s", host);
    system(cmd);

    printf("\nPress any key...");
    _getch();

    // 再度カーソル非表示
    set_cursor_visible(FALSE);

    // 再描画のため一度クリア
    system("cls");
}

int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 起動時に一度だけ画面クリア
    system("cls");

    // 現在の色属性を取得
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    defaultAttr = csbi.wAttributes;

    // カーソル状態を保存
    GetConsoleCursorInfo(hConsole, &originalCursorInfo);

    // カーソル非表示
    set_cursor_visible(FALSE);

    load_ssh_config();

    int selected = 0;

    while (1) {
        draw_menu(selected);

        int ch = _getch();

        if (ch == 'q') break;

        if (ch == 224) {
            ch = _getch();
            if (ch == 72 && selected > 0) selected--;
            if (ch == 80 && selected < host_count - 1) selected++;
        } else if (ch == 13) {
            connect_host(hosts[selected]);
        }
    }

    // 終了時にカーソル状態を復元
    SetConsoleCursorInfo(hConsole, &originalCursorInfo);

    // 色も戻す
    set_color(defaultAttr);

    // 最後に画面クリア
    system("cls");

    return 0;
}
