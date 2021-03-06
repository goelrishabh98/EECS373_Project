new_project \
    -name {WhiteboarPlotter} \
    -location {N:\EECS373_Project\WhiteBoard_Plotter\designer\impl1\WhiteboarPlotter_fp} \
    -mode {single}
set_device_type -type {A2F200M3F}
set_device_package -package {484 FBGA}
update_programming_file \
    -feature {prog_fpga:on} \
    -fdb_source {fdb} \
    -fdb_file {N:\EECS373_Project\WhiteBoard_Plotter\designer\impl1\WhiteboarPlotter.fdb} \
    -feature {prog_from:off} \
    -feature {prog_nvm:on} \
    -efm_content {location:0;source:efc} \
    -efm_block {location:0;config_file:{N:\EECS373_Project\WhiteBoard_Plotter\component\work\WhiteBoard_Plotter\MSS_ENVM_0\MSS_ENVM_0.efc}} \
    -pdb_file {N:\EECS373_Project\WhiteBoard_Plotter\designer\impl1\WhiteboarPlotter_fp\WhiteboarPlotter.pdb}
set_programming_action -action {PROGRAM}
run_selected_actions
save_project
close_project
