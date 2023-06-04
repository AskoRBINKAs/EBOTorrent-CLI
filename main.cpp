#include <iostream>
#include <libtorrent/session.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_status.hpp>
#include <progressbar.hpp>
#include <vector>
using namespace std;




//convert bytes to megabytes
float byte_to_mb(long bytes){
    return bytes/(1024*1024);
}

void multiple_download_torrents(vector<string> torrent_files, string path_to_save){
    lt::session session = lt::session();
    vector<lt::torrent_handle> handlers; //vector of handlers to control
    unsigned long size_downloaded = 0;
    unsigned long total_size = 0;
    progressbar bar(100);
    int prevPerent = 0;
    //start downloading of torrent_files
    for(auto file : torrent_files){
        lt::add_torrent_params atp = lt::add_torrent_params();
        atp.save_path = path_to_save;
        atp.ti = make_shared<lt::torrent_info>(file);
        cout << "Started downloading " << file << endl;
        lt::torrent_handle handler = session.add_torrent(atp);
        handlers.push_back(handler);
        total_size += atp.ti->total_size();
    }
    cout << "Total size of " << torrent_files.size() << " torrent files is " << byte_to_mb(total_size) << " MB\n";
    
    //main loop
    while(true){
        //calculating sum of downloaded files
        size_downloaded=0;
        for(auto handle:handlers){
            for(auto i : handle.file_progress()){
                    size_downloaded+=i;
            }
        }
        //draw progress bar
        if(total_size>0)
            {
                int percent = (size_downloaded*100)/total_size;
                
                int increment = total_size/100;
                for(int i=prevPerent+1;i<=percent;i++){
                    if(size_downloaded>=(i*increment))bar.update();
                }
                prevPerent=percent;
            }
        //check status of torrents 
        for(int i=0;i<handlers.size();i++){
            lt::torrent_status status = handlers[i].status();
            if(status.is_finished){
                cout << endl << status.name << " finished downloading\n";   
                handlers.erase(handlers.begin()+i);
            }
        }
        //exit point
        if(handlers.size()==0){
            cout << "\nAll downloads finished\n";
            break;
        }
    }

}
void download_torrent(string path_to_tf,string path_to_save){
    lt::session ses = lt::session();
    lt::add_torrent_params atp = lt::add_torrent_params();
    try{
        atp.save_path = path_to_save;
        atp.ti = std::make_shared<lt::torrent_info>(path_to_tf); // set path to torrent file
        lt::torrent_handle handle =  ses.add_torrent(atp);
        cout << "Started downloading files from " << path_to_tf <<'\n';
        unsigned long size_downloaded = 0;
        unsigned long total_size = atp.ti->total_size();
        cout << "Total size: " << byte_to_mb(total_size) << " MB"<<endl;
        progressbar bar(100); //init progress bar
        int prevPerent = 0; 
        //init main loop for downloading
        while(true){
            size_downloaded=0;
            //calcualte downloaded
            for(auto i : handle.file_progress()){
                size_downloaded+=i;
            }
            //change progress in progress bar by calucating percents of downloaded files
            if(total_size>0)
            {
                int percent = (size_downloaded*100)/total_size;
                
                int increment = total_size/100;
                for(int i=prevPerent+1;i<=percent;i++){
                    if(size_downloaded>=(i*increment))bar.update();
                }
                prevPerent=percent;
            }
            //check if downloading finished
            if(handle.status().is_finished){
                cout << "\nFinished\n";
                goto done;
                break;
            }
        }
    }
    catch(...){
        goto done;
        cout << "Catched error while downloading "<< path_to_tf << "\n";
    }
    //calling destructors of session and add_torrent_params
    done:
        cout << endl;
}

int main(int argc, char* argv[]) {
    cout << "Welcome to EBOTorrent - console torrent client for downloading files.\nVersion: 0.1-dev" << endl;
    if(argc<3){
        cout << "Usage: ./TorrentCLI <t1.torrent> <t2.torrent> ... <tN.torrent> <path_to_save>\n";
        return 0;
    }
    if(argc==3){
        download_torrent(argv[1],argv[2]);
    }
    else{
        vector<string> arg;
        for(int i=1;i<argc-1;i++){
            arg.push_back(string(argv[i]));
        }
        multiple_download_torrents(arg,argv[argc-1]);
    }

}
