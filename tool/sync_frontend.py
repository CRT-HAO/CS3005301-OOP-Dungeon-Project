"""
 # @ File: sync_frontend.py
 # @ Author: 張皓鈞(HAO) m831718@gmail.com
 # @ Create Date: 2023/06/02 00:20:51
 # @ Editor: 張皓鈞(HAO) m831718@gmail.com
 # @ Update Date: 2023/06/02 00:22:19
 # @ Description: 自動同步開發目錄的assets資料夾到build目錄
 """

import os
import platform
import shutil
import pprint
import time

# 來源目錄
src_path = "../assets/"
# 目標目錄
if platform.system() == "Windows":  # Windows Debug
    target_path = "../build/Debug/assets/"
elif platform.system() == "Darwin":  # macOS
    target_path = "../build/Dungeon.app/Contents/Resources/assets/"
else:
    target_path = "../build/assets/"
# 刷新間隔(s)
refresh_delay = 0.1

script_path = os.path.split(os.path.realpath(__file__))[0]
src_abs_path = os.path.abspath(os.path.join(script_path, src_path))
target_abs_path = os.path.abspath(os.path.join(script_path, target_path))

f1 = []
f2 = []


# 遍歷目錄(包含子目錄)
def list_dir(path, start="") -> dict:
    r = dict()
    for file in os.listdir(path):
        fpath = os.path.abspath(os.path.join(path, file))
        rpath = os.path.join(start, file)
        if os.path.isdir(fpath):
            r[rpath] = {"dir": True}
            r.update(list_dir(fpath, rpath))
        else:
            r[rpath] = {
                "dir": False,
                "time": os.path.getmtime(fpath),
            }
            # r.append({"path": d, "modified": os.path.getmtime(d)})
    return r


last_src_dir = dict()


def sync(src, target):
    global last_src_dir
    src_dir = list_dir(src)
    target_dir = list_dir(target)
    for file, info in src_dir.items():
        if file not in target_dir.keys():
            file_src_fpath = os.path.abspath(os.path.join(src_abs_path, file))
            file_target_fpath = os.path.abspath(os.path.join(target_abs_path, file))
            if info["dir"] == True:
                print("Copy Dir: " + file_src_fpath)
                print(" → " + file_target_fpath)
                # 複製資料夾
                shutil.copytree(file_src_fpath, file_target_fpath)
            else:
                print("Copy File: " + file_src_fpath)
                print(" → " + file_target_fpath)
                # 複製文件
                shutil.copy2(file_src_fpath, file_target_fpath)
        else:
            if info["dir"] == False:
                if info["time"] != target_dir[file]["time"]:
                    file_src_fpath = os.path.abspath(os.path.join(src_abs_path, file))
                    file_target_fpath = os.path.abspath(
                        os.path.join(target_abs_path, file)
                    )
                    print("Update File: " + file_src_fpath)
                    print(" → " + file_target_fpath)
                    # 複製文件(保留修改日期)
                    shutil.copy2(file_src_fpath, file_target_fpath)

    for file, info in target_dir.items():
        if file not in src_dir.keys():
            file_src_fpath = os.path.abspath(os.path.join(src_abs_path, file))
            file_target_fpath = os.path.abspath(os.path.join(target_abs_path, file))
            if info["dir"] == True:
                print("Delete Dir: " + file_src_fpath)
                print(" → " + file_target_fpath)
                try:
                    # 刪除資料夾
                    shutil.rmtree(file_target_fpath)
                except FileNotFoundError:
                    pass
            else:
                print("Delete File: " + file_src_fpath)
                print(" → " + file_target_fpath)
                try:
                    # 刪除文件
                    os.remove(file_target_fpath)
                except FileNotFoundError:
                    pass
    last_src_dir = src_dir


def main():
    print("Frontend assets sync tool V1.0")

    print("Source Path: " + src_abs_path)
    print("Target Path: " + target_abs_path)

    dir = list_dir(src_abs_path)
    print("List path file:")
    for p, t in dir.items():
        print(" - " + p)

    while True:
        sync(src_abs_path, target_abs_path)
        time.sleep(refresh_delay)


if __name__ == "__main__":
    main()
