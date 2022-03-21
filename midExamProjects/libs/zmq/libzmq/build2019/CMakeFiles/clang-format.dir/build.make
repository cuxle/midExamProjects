# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\projects\current_project\libzmq\libzmq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\projects\current_project\libzmq\build2019

# Utility rule file for clang-format.

# Include any custom commands dependencies for this target.
include CMakeFiles\clang-format.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\clang-format.dir\progress.make

CMakeFiles\clang-format:
	clang-format -style=file -i ../libzmq/include/zmq.h ../libzmq/include/zmq_utils.h ../libzmq/perf/benchmark_radix_tree.cpp ../libzmq/perf/inproc_lat.cpp ../libzmq/perf/inproc_thr.cpp ../libzmq/perf/local_lat.cpp ../libzmq/perf/local_thr.cpp ../libzmq/perf/proxy_thr.cpp ../libzmq/perf/remote_lat.cpp ../libzmq/perf/remote_thr.cpp ../libzmq/src/address.cpp ../libzmq/src/address.hpp ../libzmq/src/array.hpp ../libzmq/src/atomic_counter.hpp ../libzmq/src/atomic_ptr.hpp ../libzmq/src/blob.hpp ../libzmq/src/channel.cpp ../libzmq/src/channel.hpp ../libzmq/src/client.cpp ../libzmq/src/client.hpp ../libzmq/src/clock.cpp ../libzmq/src/clock.hpp ../libzmq/src/command.hpp ../libzmq/src/compat.hpp ../libzmq/src/condition_variable.hpp ../libzmq/src/config.hpp ../libzmq/src/ctx.cpp ../libzmq/src/ctx.hpp ../libzmq/src/curve_client.cpp ../libzmq/src/curve_client.hpp ../libzmq/src/curve_client_tools.hpp ../libzmq/src/curve_mechanism_base.cpp ../libzmq/src/curve_mechanism_base.hpp ../libzmq/src/curve_server.cpp ../libzmq/src/curve_server.hpp ../libzmq/src/dbuffer.hpp ../libzmq/src/dealer.cpp ../libzmq/src/dealer.hpp ../libzmq/src/decoder.hpp ../libzmq/src/decoder_allocators.cpp ../libzmq/src/decoder_allocators.hpp ../libzmq/src/devpoll.cpp ../libzmq/src/devpoll.hpp ../libzmq/src/dgram.cpp ../libzmq/src/dgram.hpp ../libzmq/src/dish.cpp ../libzmq/src/dish.hpp ../libzmq/src/dist.cpp ../libzmq/src/dist.hpp ../libzmq/src/encoder.hpp ../libzmq/src/endpoint.cpp ../libzmq/src/endpoint.hpp ../libzmq/src/epoll.cpp ../libzmq/src/epoll.hpp ../libzmq/src/err.cpp ../libzmq/src/err.hpp ../libzmq/src/fd.hpp ../libzmq/src/fq.cpp ../libzmq/src/fq.hpp ../libzmq/src/gather.cpp ../libzmq/src/gather.hpp ../libzmq/src/generic_mtrie.hpp ../libzmq/src/generic_mtrie_impl.hpp ../libzmq/src/gssapi_client.cpp ../libzmq/src/gssapi_client.hpp ../libzmq/src/gssapi_mechanism_base.cpp ../libzmq/src/gssapi_mechanism_base.hpp ../libzmq/src/gssapi_server.cpp ../libzmq/src/gssapi_server.hpp ../libzmq/src/i_decoder.hpp ../libzmq/src/i_encoder.hpp ../libzmq/src/i_engine.hpp ../libzmq/src/i_mailbox.hpp ../libzmq/src/i_poll_events.hpp ../libzmq/src/io_object.cpp ../libzmq/src/io_object.hpp ../libzmq/src/io_thread.cpp ../libzmq/src/io_thread.hpp ../libzmq/src/ip.cpp ../libzmq/src/ip.hpp ../libzmq/src/ip_resolver.cpp ../libzmq/src/ip_resolver.hpp ../libzmq/src/ipc_address.cpp ../libzmq/src/ipc_address.hpp ../libzmq/src/ipc_connecter.cpp ../libzmq/src/ipc_connecter.hpp ../libzmq/src/ipc_listener.cpp ../libzmq/src/ipc_listener.hpp ../libzmq/src/kqueue.cpp ../libzmq/src/kqueue.hpp ../libzmq/src/lb.cpp ../libzmq/src/lb.hpp ../libzmq/src/likely.hpp ../libzmq/src/macros.hpp ../libzmq/src/mailbox.cpp ../libzmq/src/mailbox.hpp ../libzmq/src/mailbox_safe.cpp ../libzmq/src/mailbox_safe.hpp ../libzmq/src/mechanism.cpp ../libzmq/src/mechanism.hpp ../libzmq/src/mechanism_base.cpp ../libzmq/src/mechanism_base.hpp ../libzmq/src/metadata.cpp ../libzmq/src/metadata.hpp ../libzmq/src/msg.cpp ../libzmq/src/msg.hpp ../libzmq/src/mtrie.cpp ../libzmq/src/mtrie.hpp ../libzmq/src/mutex.hpp ../libzmq/src/norm_engine.cpp ../libzmq/src/norm_engine.hpp ../libzmq/src/null_mechanism.cpp ../libzmq/src/null_mechanism.hpp ../libzmq/src/object.cpp ../libzmq/src/object.hpp ../libzmq/src/options.cpp ../libzmq/src/options.hpp ../libzmq/src/own.cpp ../libzmq/src/own.hpp ../libzmq/src/pair.cpp ../libzmq/src/pair.hpp ../libzmq/src/peer.cpp ../libzmq/src/peer.hpp ../libzmq/src/pgm_receiver.cpp ../libzmq/src/pgm_receiver.hpp ../libzmq/src/pgm_sender.cpp ../libzmq/src/pgm_sender.hpp ../libzmq/src/pgm_socket.cpp ../libzmq/src/pgm_socket.hpp ../libzmq/src/pipe.cpp ../libzmq/src/pipe.hpp ../libzmq/src/plain_client.cpp ../libzmq/src/plain_client.hpp ../libzmq/src/plain_common.hpp ../libzmq/src/plain_server.cpp ../libzmq/src/plain_server.hpp ../libzmq/src/poll.cpp ../libzmq/src/poll.hpp ../libzmq/src/poller.hpp ../libzmq/src/poller_base.cpp ../libzmq/src/poller_base.hpp ../libzmq/src/polling_util.cpp ../libzmq/src/polling_util.hpp ../libzmq/src/pollset.cpp ../libzmq/src/pollset.hpp ../libzmq/src/precompiled.cpp ../libzmq/src/precompiled.hpp ../libzmq/src/proxy.cpp ../libzmq/src/proxy.hpp ../libzmq/src/pub.cpp ../libzmq/src/pub.hpp ../libzmq/src/pull.cpp ../libzmq/src/pull.hpp ../libzmq/src/push.cpp ../libzmq/src/push.hpp ../libzmq/src/radio.cpp ../libzmq/src/radio.hpp ../libzmq/src/radix_tree.cpp ../libzmq/src/radix_tree.hpp ../libzmq/src/random.cpp ../libzmq/src/random.hpp ../libzmq/src/raw_decoder.cpp ../libzmq/src/raw_decoder.hpp ../libzmq/src/raw_encoder.cpp ../libzmq/src/raw_encoder.hpp ../libzmq/src/raw_engine.cpp ../libzmq/src/raw_engine.hpp ../libzmq/src/reaper.cpp ../libzmq/src/reaper.hpp ../libzmq/src/rep.cpp ../libzmq/src/rep.hpp ../libzmq/src/req.cpp ../libzmq/src/req.hpp ../libzmq/src/router.cpp ../libzmq/src/router.hpp ../libzmq/src/scatter.cpp ../libzmq/src/scatter.hpp ../libzmq/src/secure_allocator.hpp ../libzmq/src/select.cpp ../libzmq/src/select.hpp ../libzmq/src/server.cpp ../libzmq/src/server.hpp ../libzmq/src/session_base.cpp ../libzmq/src/session_base.hpp ../libzmq/src/signaler.cpp ../libzmq/src/signaler.hpp ../libzmq/src/socket_base.cpp ../libzmq/src/socket_base.hpp ../libzmq/src/socket_poller.cpp ../libzmq/src/socket_poller.hpp ../libzmq/src/socks.cpp ../libzmq/src/socks.hpp ../libzmq/src/socks_connecter.cpp ../libzmq/src/socks_connecter.hpp ../libzmq/src/stdint.hpp ../libzmq/src/stream.cpp ../libzmq/src/stream.hpp ../libzmq/src/stream_connecter_base.cpp ../libzmq/src/stream_connecter_base.hpp ../libzmq/src/stream_engine_base.cpp ../libzmq/src/stream_engine_base.hpp ../libzmq/src/stream_listener_base.cpp ../libzmq/src/stream_listener_base.hpp ../libzmq/src/sub.cpp ../libzmq/src/sub.hpp ../libzmq/src/tcp.cpp ../libzmq/src/tcp.hpp ../libzmq/src/tcp_address.cpp ../libzmq/src/tcp_address.hpp ../libzmq/src/tcp_connecter.cpp ../libzmq/src/tcp_connecter.hpp ../libzmq/src/tcp_listener.cpp ../libzmq/src/tcp_listener.hpp ../libzmq/src/thread.cpp ../libzmq/src/thread.hpp ../libzmq/src/timers.cpp ../libzmq/src/timers.hpp ../libzmq/src/tipc_address.cpp ../libzmq/src/tipc_address.hpp ../libzmq/src/tipc_connecter.cpp ../libzmq/src/tipc_connecter.hpp ../libzmq/src/tipc_listener.cpp ../libzmq/src/tipc_listener.hpp ../libzmq/src/trie.cpp ../libzmq/src/trie.hpp ../libzmq/src/tweetnacl.h ../libzmq/src/udp_address.cpp ../libzmq/src/udp_address.hpp ../libzmq/src/udp_engine.cpp ../libzmq/src/udp_engine.hpp ../libzmq/src/v1_decoder.cpp ../libzmq/src/v1_decoder.hpp ../libzmq/src/v1_encoder.cpp ../libzmq/src/v1_encoder.hpp ../libzmq/src/v2_decoder.cpp ../libzmq/src/v2_decoder.hpp ../libzmq/src/v2_encoder.cpp ../libzmq/src/v2_encoder.hpp ../libzmq/src/v2_protocol.hpp ../libzmq/src/v3_1_encoder.cpp ../libzmq/src/v3_1_encoder.hpp ../libzmq/src/vmci.cpp ../libzmq/src/vmci.hpp ../libzmq/src/vmci_address.cpp ../libzmq/src/vmci_address.hpp ../libzmq/src/vmci_connecter.cpp ../libzmq/src/vmci_connecter.hpp ../libzmq/src/vmci_listener.cpp ../libzmq/src/vmci_listener.hpp ../libzmq/src/windows.hpp ../libzmq/src/wire.hpp ../libzmq/src/ws_address.cpp ../libzmq/src/ws_address.hpp ../libzmq/src/ws_connecter.cpp ../libzmq/src/ws_connecter.hpp ../libzmq/src/ws_decoder.cpp ../libzmq/src/ws_decoder.hpp ../libzmq/src/ws_encoder.cpp ../libzmq/src/ws_encoder.hpp ../libzmq/src/ws_engine.cpp ../libzmq/src/ws_engine.hpp ../libzmq/src/ws_listener.cpp ../libzmq/src/ws_listener.hpp ../libzmq/src/ws_protocol.hpp ../libzmq/src/wss_address.cpp ../libzmq/src/wss_address.hpp ../libzmq/src/wss_engine.cpp ../libzmq/src/wss_engine.hpp ../libzmq/src/xpub.cpp ../libzmq/src/xpub.hpp ../libzmq/src/xsub.cpp ../libzmq/src/xsub.hpp ../libzmq/src/ypipe.hpp ../libzmq/src/ypipe_base.hpp ../libzmq/src/ypipe_conflate.hpp ../libzmq/src/yqueue.hpp ../libzmq/src/zap_client.cpp ../libzmq/src/zap_client.hpp ../libzmq/src/zmq.cpp ../libzmq/src/zmq_draft.h ../libzmq/src/zmq_utils.cpp ../libzmq/src/zmtp_engine.cpp ../libzmq/src/zmtp_engine.hpp ../libzmq/tests/test_abstract_ipc.cpp ../libzmq/tests/test_address_tipc.cpp ../libzmq/tests/test_ancillaries.cpp ../libzmq/tests/test_app_meta.cpp ../libzmq/tests/test_atomics.cpp ../libzmq/tests/test_base85.cpp ../libzmq/tests/test_bind_after_connect_tcp.cpp ../libzmq/tests/test_bind_curve_fuzzer.cpp ../libzmq/tests/test_bind_fuzzer.cpp ../libzmq/tests/test_bind_null_fuzzer.cpp ../libzmq/tests/test_bind_src_address.cpp ../libzmq/tests/test_bind_stream_fuzzer.cpp ../libzmq/tests/test_bind_ws_fuzzer.cpp ../libzmq/tests/test_busy_poll.cpp ../libzmq/tests/test_capabilities.cpp ../libzmq/tests/test_channel.cpp ../libzmq/tests/test_client_server.cpp ../libzmq/tests/test_conflate.cpp ../libzmq/tests/test_connect_curve_fuzzer.cpp ../libzmq/tests/test_connect_delay_tipc.cpp ../libzmq/tests/test_connect_fuzzer.cpp ../libzmq/tests/test_connect_null_fuzzer.cpp ../libzmq/tests/test_connect_resolve.cpp ../libzmq/tests/test_connect_rid.cpp ../libzmq/tests/test_connect_stream_fuzzer.cpp ../libzmq/tests/test_connect_ws_fuzzer.cpp ../libzmq/tests/test_ctx_destroy.cpp ../libzmq/tests/test_ctx_options.cpp ../libzmq/tests/test_dgram.cpp ../libzmq/tests/test_diffserv.cpp ../libzmq/tests/test_disconnect_inproc.cpp ../libzmq/tests/test_disconnect_msg.cpp ../libzmq/tests/test_filter_ipc.cpp ../libzmq/tests/test_fork.cpp ../libzmq/tests/test_getsockopt_memset.cpp ../libzmq/tests/test_heartbeats.cpp ../libzmq/tests/test_hello_msg.cpp ../libzmq/tests/test_hiccup_msg.cpp ../libzmq/tests/test_hwm.cpp ../libzmq/tests/test_hwm_pubsub.cpp ../libzmq/tests/test_immediate.cpp ../libzmq/tests/test_inproc_connect.cpp ../libzmq/tests/test_invalid_rep.cpp ../libzmq/tests/test_iov.cpp ../libzmq/tests/test_ipc_wildcard.cpp ../libzmq/tests/test_issue_566.cpp ../libzmq/tests/test_last_endpoint.cpp ../libzmq/tests/test_many_sockets.cpp ../libzmq/tests/test_metadata.cpp ../libzmq/tests/test_mock_pub_sub.cpp ../libzmq/tests/test_monitor.cpp ../libzmq/tests/test_msg_ffn.cpp ../libzmq/tests/test_msg_flags.cpp ../libzmq/tests/test_msg_init.cpp ../libzmq/tests/test_pair_inproc.cpp ../libzmq/tests/test_pair_ipc.cpp ../libzmq/tests/test_pair_tcp.cpp ../libzmq/tests/test_pair_tcp_cap_net_admin.cpp ../libzmq/tests/test_pair_tipc.cpp ../libzmq/tests/test_pair_vmci.cpp ../libzmq/tests/test_peer.cpp ../libzmq/tests/test_poller.cpp ../libzmq/tests/test_probe_router.cpp ../libzmq/tests/test_proxy.cpp ../libzmq/tests/test_proxy_hwm.cpp ../libzmq/tests/test_proxy_single_socket.cpp ../libzmq/tests/test_proxy_terminate.cpp ../libzmq/tests/test_pub_invert_matching.cpp ../libzmq/tests/test_pubsub.cpp ../libzmq/tests/test_radio_dish.cpp ../libzmq/tests/test_rebind_ipc.cpp ../libzmq/tests/test_reconnect_ivl.cpp ../libzmq/tests/test_reconnect_options.cpp ../libzmq/tests/test_req_correlate.cpp ../libzmq/tests/test_req_relaxed.cpp ../libzmq/tests/test_reqrep_device.cpp ../libzmq/tests/test_reqrep_device_tipc.cpp ../libzmq/tests/test_reqrep_inproc.cpp ../libzmq/tests/test_reqrep_ipc.cpp ../libzmq/tests/test_reqrep_tcp.cpp ../libzmq/tests/test_reqrep_tipc.cpp ../libzmq/tests/test_reqrep_vmci.cpp ../libzmq/tests/test_router_handover.cpp ../libzmq/tests/test_router_mandatory.cpp ../libzmq/tests/test_router_mandatory_hwm.cpp ../libzmq/tests/test_router_mandatory_tipc.cpp ../libzmq/tests/test_router_notify.cpp ../libzmq/tests/test_scatter_gather.cpp ../libzmq/tests/test_security_curve.cpp ../libzmq/tests/test_security_gssapi.cpp ../libzmq/tests/test_security_no_zap_handler.cpp ../libzmq/tests/test_security_null.cpp ../libzmq/tests/test_security_plain.cpp ../libzmq/tests/test_security_zap.cpp ../libzmq/tests/test_setsockopt.cpp ../libzmq/tests/test_shutdown_stress.cpp ../libzmq/tests/test_shutdown_stress_tipc.cpp ../libzmq/tests/test_socket_null.cpp ../libzmq/tests/test_socket_options_fuzzer.cpp ../libzmq/tests/test_sockopt_hwm.cpp ../libzmq/tests/test_socks.cpp ../libzmq/tests/test_sodium.cpp ../libzmq/tests/test_spec_dealer.cpp ../libzmq/tests/test_spec_pushpull.cpp ../libzmq/tests/test_spec_rep.cpp ../libzmq/tests/test_spec_req.cpp ../libzmq/tests/test_spec_router.cpp ../libzmq/tests/test_srcfd.cpp ../libzmq/tests/test_stream.cpp ../libzmq/tests/test_stream_disconnect.cpp ../libzmq/tests/test_stream_empty.cpp ../libzmq/tests/test_stream_exceeds_buffer.cpp ../libzmq/tests/test_stream_timeout.cpp ../libzmq/tests/test_sub_forward.cpp ../libzmq/tests/test_sub_forward_tipc.cpp ../libzmq/tests/test_system.cpp ../libzmq/tests/test_tcp_accept_filter.cpp ../libzmq/tests/test_term_endpoint.cpp ../libzmq/tests/test_term_endpoint_tipc.cpp ../libzmq/tests/test_thread_safe.cpp ../libzmq/tests/test_timeo.cpp ../libzmq/tests/test_timers.cpp ../libzmq/tests/test_unbind_wildcard.cpp ../libzmq/tests/test_use_fd.cpp ../libzmq/tests/test_ws_transport.cpp ../libzmq/tests/test_wss_transport.cpp ../libzmq/tests/test_xpub_manual.cpp ../libzmq/tests/test_xpub_manual_last_value.cpp ../libzmq/tests/test_xpub_nodrop.cpp ../libzmq/tests/test_xpub_verbose.cpp ../libzmq/tests/test_xpub_welcome_msg.cpp ../libzmq/tests/test_xsub_verbose.cpp ../libzmq/tests/test_z85_decode_fuzzer.cpp ../libzmq/tests/test_zmq_poll_fd.cpp ../libzmq/tests/test_zmq_ppoll_fd.cpp ../libzmq/tests/test_zmq_ppoll_signals.cpp ../libzmq/tests/testutil.cpp ../libzmq/tests/testutil.hpp ../libzmq/tests/testutil_monitoring.cpp ../libzmq/tests/testutil_monitoring.hpp ../libzmq/tests/testutil_security.cpp ../libzmq/tests/testutil_security.hpp ../libzmq/tests/testutil_unity.cpp ../libzmq/tests/testutil_unity.hpp ../libzmq/tools/curve_keygen.cpp

clang-format: CMakeFiles\clang-format
clang-format: CMakeFiles\clang-format.dir\build.make
.PHONY : clang-format

# Rule to build all files generated by this target.
CMakeFiles\clang-format.dir\build: clang-format
.PHONY : CMakeFiles\clang-format.dir\build

CMakeFiles\clang-format.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\clang-format.dir\cmake_clean.cmake
.PHONY : CMakeFiles\clang-format.dir\clean

CMakeFiles\clang-format.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" E:\projects\current_project\libzmq\libzmq E:\projects\current_project\libzmq\libzmq E:\projects\current_project\libzmq\build2019 E:\projects\current_project\libzmq\build2019 E:\projects\current_project\libzmq\build2019\CMakeFiles\clang-format.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\clang-format.dir\depend

