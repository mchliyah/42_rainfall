undefined4 main(undefined4 param_1,int param_2)

{
  int i;
  char *str;
  undefined4 local_1c;
  __uid_t local_18;
  __gid_t local_14;
  
  i = atoi(*(char **)(param_2 + 4));
  if (i == 0x1a7) {
    str = strdup("/bin/sh");
    local_1c = 0;
    local_14 = getegid();
    local_18 = geteuid();
    setresgid(local_14,local_14,local_14);
    setresuid(local_18,local_18,local_18);
    execv("/bin/sh",&str);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}
