##Implemented RPCs:
###interface-server: lookup
###interface-server: update
###server-server: post_update
###server-server/interface:post_failure

##Implemented:
###client (with a CLI interface)
###server
###interface

##To be Done:
###Test(currently only tested on localhost)

##Issues
###Current implementation: when main server fails, it actually exits
###Needs to restart as bakcup manually
###But that should be Okay

##Demo 
###Tip: sudo fix_auth_error if rpc register fails
###steps:
###run "./interface localhost localhost" in demo/
###run "./server m localhost" in demo/sv1/server
###run "./server b localhost" in demo/sv2/server
###
###run "./client" in demo/
###GO!

###Note: When server m (the primary server) fails
###Run "./server b localhost" manually to restart as bakcup server    
