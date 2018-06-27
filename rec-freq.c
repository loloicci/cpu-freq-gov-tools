#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int usage_exit(){
  fprintf(stderr, "Usage: $0 [-h] [-i interval sec] [-t end sec] [-o output file] [-c core counts] commands");
  exit(1);
}

void write_first_line(FILE *fp, FILE **files, int core){
  char line[1024] = "time";
  char f[256];
  for(int i = 0; i < core; i++){
    fgets(f, 256, files[i]);
    for(int j = 0; j < 256; j++){
      if(f[j] == '\n'){
        f[j] = '\0';
        break;
      }
    }
    strncat(line, ", ", 1024);
    strncat(line, f, 1024);
    fclose(files[i]);
  }
  fprintf(fp, "%s\n", line);
}

void write_line(FILE *fp, FILE **files, int core, char names[][256]){
  char line[1024] = "";
  char f[256];
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  sprintf(line, "%ld.%09ld", ts.tv_sec, ts.tv_nsec);
  for(int i = 0; i < core; i++){
    freopen(names[i], "r", files[i]);
    fgets(f, 256, files[i]);
    for(int j = 0; j < 256; j++){
      if(f[j] == '\n'){
        f[j] = '\0';
        break;
      }
    }
    strncat(line, ", ", 1024);
    strncat(line, f, 1024);
  }
  fprintf(fp, "%s\n", line);
}

int main(int argc, char *argv[]){
  int result;
  long interval = 8000;
  char out[256] = "./out.csv";
  int core = 8;
  long time = 300000;
  long time_spend = 0;
  while((result=getopt(argc, argv, "o:i:t:c:h"))!=-1){
    switch(result){
    case 'o':
      strncpy(out, optarg, 256);
      break;
    case 'i':
      interval = atol(optarg);
      break;
    case 't':
      time = atol(optarg);
      break;
    case 'c':
      core = atoi(optarg);
      break;
    case 'h':
      usage_exit();
      break;
    }
  }

  FILE *gov_f[core];
  FILE *freq_f[core];
  char freq[core][256];
  FILE *of;
  for(int i = 0; i < core; i++){
    char gov[256];
    sprintf(gov, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", i);
    sprintf(freq[i], "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", i);
    freq_f[i] = fopen(freq[i], "r");
    gov_f[i] = fopen(gov, "r");
  }
  of = fopen(out, "w");
  write_first_line(of, gov_f, core);

  while(time_spend < time){
    write_line(of, freq_f, core, freq);
    time_spend += (interval / 1000);
    usleep(interval);
  }
  fclose(of);
  exit(0);
}
