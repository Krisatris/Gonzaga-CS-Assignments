<template>
    <div id="app">
        
        <h1>Group Four's Routing Project</h1>

        <svg height="600" width="1000">

            <!--lines-->
            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="250" y="120"  :style="{visibility: (!this.line_removed[19] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[19]}}</text>
            <line id="9-10" x1="200" y1="125" x2="300" y2="125" :class="get_line(19) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[19] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="350" y="120"  :style="{visibility: (!this.line_removed[20] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[20]}}</text>
            <line id="10-11-" x1="300" y1="125" x2="400" y2="125" :class="get_line(20) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[20] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="250" y="220"  :style="{visibility: (!this.line_removed[11] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[11]}}</text>
            <line id="5-6" x1="200" y1="225" x2="300" y2="225" :class="get_line(11) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[11] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="150" y="220"  :style="{visibility: (!this.line_removed[10] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[10]}}</text>
            <line id="4-5" x1="100" y1="225" x2="200" y2="225" :class="get_line(10) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[10] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)" />

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="350" y="220"  :style="{visibility: (!this.line_removed[12] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[12]}}</text>
            <line id="6-7" x1="300" y1="225" x2="400" y2="225" :class="get_line(12) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[12] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="450" y="220" :style="{visibility: (!this.line_removed[13] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[13]}}</text>
            <line id="7-8" x1="400" y1="225" x2="500" y2="225" :class="get_line(13) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[13] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="250" y="320" :style="{visibility: (!this.line_removed[3] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[3]}}</text>
            <line id="1-2" x1="200" y1="325" x2="300" y2="325" :class="get_line(3) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[3] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="350" y="320"  :style="{visibility: (!this.line_removed[4] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[4]}}</text>
            <line id="2-3" x1="300" y1="325" x2="400" y2="325" :class="get_line(4) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[4] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="295" y="80" :style="{visibility: (!this.line_removed[22] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[22]}}</text>
            <line id="10-12" x1="300" y1="25" x2="300" y2="125" :class="get_line(22) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[22] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="295" y="180"  :style="{visibility: (!this.line_removed[16] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[16]}}</text>
            <line id="6-10" x1="300" y1="125" x2="300" y2="225" :class="get_line(16) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[16] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="190" y="180"  :style="{visibility: (!this.line_removed[15] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[15]}}</text>
            <line id="5-9" x1="200" y1="125" x2="200" y2="225" :class="get_line(15) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[15] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="390" y="180"  :style="{visibility: (!this.line_removed[17] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[17]}}</text>
            <line id="7-11" x1="400" y1="125" x2="400" y2="225" :class="get_line(17) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[17] ? 'visible' : 'hidden'), 'stroke-width':2}"  @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="395" y="280"  :style="{visibility: (!this.line_removed[8] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[8]}}</text>
            <line id="3-7" x1="400" y1="225" x2="400" y2="325" :class="get_line(8) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[8] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="290" y="280" :style="{visibility: (!this.line_removed[7] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[7]}}</text>
            <line id="2-6" x1="300" y1="225" x2="300" y2="325" :class="get_line(7) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[7] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)" />

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="195" y="280"  :style="{visibility: (!this.line_removed[6] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[6]}}</text>
            <line id="1-5" x1="200" y1="225" x2="200" y2="325" :class="get_line(6) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[6] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="290" y="380" :style="{visibility: (!this.line_removed[1] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[1]}}</text>
            <line id="0-2" x1="300" y1="325" x2="300" y2="425" :class="get_line(1) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[1] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="245" y="70"  :style="{visibility: (!this.line_removed[21] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[21]}}</text>
            <line id="9-12" x1="300" y1="25" x2="200" y2="125" :class="get_line(21) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[21] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="145" y="170"  :style="{visibility: (!this.line_removed[14] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[14]}}</text>
            <line id="4-9" x1="200" y1="125" x2="100" y2="225" :class="get_line(14) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[14] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)" />

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="145" y="290"  :style="{visibility: (!this.line_removed[5] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[5]}}</text>
            <line id="1-4" x1="100" y1="225" x2="200" y2="325" :class="get_line(5) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[5] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="245" y="390"  :style="{visibility: (!this.line_removed[0] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[0]}}</text>
            <line id="0-1" x1="200" y1="325" x2="300" y2="425" :class="get_line(0) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[0] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="355" y="390"  :style="{visibility: (!this.line_removed[2] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[2]}}</text>
            <line id="0-3" x1="300" y1="425" x2="400" y2="325" :class="get_line(2) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[2] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)" />

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="455" y="290"  :style="{visibility: (!this.line_removed[9] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[9]}}</text>
            <line id="3-8" x1="400" y1="325" x2="500" y2="225" :class="get_line(9) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[9] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="450" y="170"  :style="{visibility: (!this.line_removed[18] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[18]}}</text>
            <line id="8-11" x1="500" y1="225" x2="400" y2="125" :class="get_line(18) ? 'red' : 'black'" :style="{visibility: (!this.line_removed[18] ? 'visible' : 'hidden'), 'stroke-width':2}" @click="show_update($event)"/>

            <text fill="#ffhwff" font-size="12" font-family="Verdana" x="355" y="70"  :style="{visibility: (!this.line_removed[23] ? 'visible' : 'hidden')}" text-anchor="middle">{{this.line_weights[23]}}</text>
            <line id="11-12" x1="400" y1="125" x2="300" y2="25" :class="get_line(23) ? 'red' : 'black'"  :style="{visibility: (!this.line_removed[23] ? 'visible' : 'hidden'), 'stroke-width':2}"  @click="show_update($event)" />

            <!--Nodes-->
            <circle id="12" cx="300" cy="25" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="12" fill="#white" font-size="20" font-family="Verdana" x="300" y="25" text-anchor="middle" dy=".3em" @click="set_route($event)">12</text>

            <circle id="9" cx="200" cy="125" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="9" fill="#white" font-size="20" font-family="Verdana" x="200" y="125" text-anchor="middle" dy=".3em" @click="set_route($event)">9</text>

            <circle id="10" cx="300" cy="125" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="10" fill="#white" font-size="20" font-family="Verdana" x="300" y="125" text-anchor="middle" dy=".3em" @click="set_route($event)">10</text>

            <circle id="11" cx="400" cy="125" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="11" fill="#white" font-size="20" font-family="Verdana" x="400" y="125" text-anchor="middle" dy=".3em" @click="set_route($event)">11</text>

            <circle id="4" cx="100" cy="225" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="4" fill="#white" font-size="20" font-family="Verdana" x="100" y="225" text-anchor="middle" dy=".3em" @click="set_route($event)">4</text>

            <circle id="5" cx="200" cy="225" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="5" fill="#white" font-size="20" font-family="Verdana" x="200" y="225" text-anchor="middle" dy=".3em" @click="set_route($event)">5</text>

            <circle id="6" cx="300" cy="225" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="6" fill="#white" font-size="20" font-family="Verdana" x="300" y="225" text-anchor="middle" dy=".3em" @click="set_route($event)">6</text>

            <circle id="7" cx="400" cy="225" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="7" fill="#white" font-size="20" font-family="Verdana" x="400" y="225" text-anchor="middle" dy=".3em" @click="set_route($event)">7</text>

            <circle id="8" cx="500" cy="225" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="8" fill="#white" font-size="20" font-family="Verdana" x="500" y="225" text-anchor="middle" dy=".3em" @click="set_route($event)">8</text>

            <circle id="1" cx="200" cy="325" r="25" fill="#aeaeae" @click="set_route($event)" />
            <text id="1" fill="#white" font-size="20" font-family="Verdana" x="200" y="325" text-anchor="middle" dy=".3em" @click="set_route($event)">1</text>

            <circle id="2" cx="300" cy="325" r="25" fill="#aeaeae" @click="set_route($event)"/>
            <text id="2" fill="#white" font-size="20" font-family="Verdana" x="300" y="325" text-anchor="middle" dy=".3em" @click="set_route($event)">2</text>

            <circle id="3" cx="400" cy="325" r="25" fill="#aeaeae" @click="set_route($event)" />
            <text id="3" fill="#white" font-size="20" font-family="Verdana" x="400" y="325" text-anchor="middle" dy=".3em" @click="set_route($event)">3</text>

            <circle id="0" cx="300" cy="425" r="25" fill="#aeaeae" @click="set_route($event)" />
            <text id="0" fill="#white" font-size="20" font-family="Verdana" x="300" y="425" text-anchor="middle" dy=".3em" @click="set_route($event)">0</text>
        </svg>

        <div>
            <p>
                How to use:<br />
                Click on any two nodes to see the shortest path between them<br />
                Click on an edge (not the edge weight!) to update or delete the edge<br />
                Use the Reset src and dest button to reset the routing algorithm for re-simulation
            </p>
        </div>

        <div>
            <button type="button" @click="reset()"> Reset src and dest</button>
        </div>
        <div>
            <button type="button" :style="{visibility: show_update_info ? 'visible' : 'hidden'}" @click="remove_edge()">Remove edge</button>
        </div>
        <br/>
        <div>
            <input type="text" v-model="update_weight" :style="{visibility: show_update_info ? 'visible' : 'hidden'}" /> <button type="button" :style="{visibility: show_update_info ? 'visible' : 'hidden'}" @click="update_edge()" v-bind:disabled="update_weight_condition">Update edge</button>
        </div>
            
    </div>
</template>

<script>
    import Home from './components/Home.vue';
    //import Title from './components/Title.vue';
    //import PathComponent from './components/PathComponent.vue';
    //import Node from './components/Node.vue';
    import { Graph, LinkedList, Node, dijkstra, addEdge, updateEdge, removeEdge } from '../src/testGraph.js';

    //var graph = require('../src/graph.js');

    export default {
        name: 'app',
        components: {
            Home,
            //PathComponent,
            //Node
        },
        data() {
            return {
                graph: new Graph(13),
                list: new LinkedList(),
                node: new Node(),
                id1: 1,
                source: -1,
                dest: -1,
                have_route: false,
                have_source: false,
                have_dest: false,
                show_update_info: false,
                src_update: -1,
                dest_update: -1,
                update_weight: null,
                paths: [],
                route_path: [],
                line_chosen: [],
                line_removed: [],
                line_weights: [11,15,14,9,13,2,6,13,4,3,12,10,13,4,10,13,2,7,4,8,8,10,3,13],
                line_ids: ['0-1', '0-2', '0-3', '1-2', '2-3', '1-4', '1-5', '2-6', '3-7', '3-8', '4-5',
                           '5-6', '6-7', '7-8', '4-9', '5-9', '6-10', '7-11', '8-11', '9-10', '10-11', '9-12', '10-12', '11-12'],
            }
        },
        created: function () {
            for (let i = 0; i < 24; ++i) {
                this.line_chosen[i] = false;
                this.line_removed[i] = false;
            } 
        },
        mounted: function () {
            
            //line_chosen = line_chosen_copy;

            addEdge(this.graph, 0, 1, 11);
            addEdge(this.graph, 0, 2, 15);
            addEdge(this.graph, 0, 3, 14);
            addEdge(this.graph, 1, 2, 9);
            addEdge(this.graph, 1, 4, 2);
            addEdge(this.graph, 1, 5, 6);
            addEdge(this.graph, 2, 6, 13);
            addEdge(this.graph, 2, 3, 13);
            addEdge(this.graph, 3, 7, 4);
            addEdge(this.graph, 3, 8, 3);
            addEdge(this.graph, 4, 5, 12);
            addEdge(this.graph, 4, 9, 10);
            addEdge(this.graph, 5, 6, 10);
            addEdge(this.graph, 5, 9, 13);
            addEdge(this.graph, 6, 10, 2);
            addEdge(this.graph, 6, 7, 13);
            addEdge(this.graph, 7, 8, 4);
            addEdge(this.graph, 7, 11, 7);
            addEdge(this.graph, 8, 11, 4);
            addEdge(this.graph, 9, 10, 8);
            addEdge(this.graph, 9, 12, 10);
            addEdge(this.graph, 10, 12, 3);
            addEdge(this.graph, 10, 11, 8);
            addEdge(this.graph, 11, 12, 13);
        },
        computed: {
            update_weight_condition() {
                /* eslint-disable no-console */
                console.log("condition wieght");
                console.log(this.update_weight);
                console.log(this.update_weight <= 0);
                if(!this.update_weight)
                    return false;
                if (this.update_weight <= 0) {
                    return false
                }
                else {
                    return null
                }
                    
            }
        },
        methods: {
            get_line(id) {
                /* eslint-disable no-console */
                console.log(id + " " + this.line_chosen[id]);
                return this.line_chosen[id];
            },
            reset() {
            /* eslint-disable no-console */
                console.log("reset");
                for (let i = 0; i < 24; ++i) {
                    this.$set(this.line_chosen, i, false)
                } 
                this.have_source = false;
                this.have_dest = false;
                this.have_route = false;

            },
            get_route: function () {
                this.paths = dijkstra(this.graph, this.source);
                this.route_path = this.tracePath(this.paths, this.source, this.dest);
                this.have_route = true;
                /* eslint-disable no-console */
                console.log(this.route_path);
                this.render_route();
            },
            set_route(element) {
                //this.test_graph();
                /* eslint-disable no-console */
                console.log("setting route" + element.currentTarget.id);
                if (!this.have_route) {
                    if (!this.have_source) {
                        this.source = element.currentTarget.id;
                        this.have_source = true;
                        console.log("source is " + this.source);
                    } else {
                        if (!this.have_dest) {
                            this.dest = element.currentTarget.id;
                            this.have_dest = true;
                            console.log("dest is " + this.dest);
                        }
                    }
                    if (this.have_source && this.have_dest) {
                        this.get_route();
                    }
                }
            },
            render_route: function () {
                /* eslint-disable no-console */
                console.log("route");
                for (let i = this.route_path.length - 1; i > 0; --i) {
                    let id;
                    if(this.route_path[i]<this.route_path[i-1])
                        id = "" + this.route_path[i] + "-" + this.route_path[i - 1];
                    else
                        id = "" + this.route_path[i-1] + "-" + this.route_path[i];
                    console.log("painting path " + id);
                    let index = this.line_ids.indexOf(id);
                    console.log(index);
                    //this.line_chosen[index] = true;
                    this.$set(this.line_chosen, index, true)
                    console.log(this.line_chosen[index]);
                }
            },
            tracePath(parents, source, destination) {
                let path = [];
                path.push(destination);
                this.tracePathRec(path, parents, destination, source);
                return path;
            },
            tracePathRec(path, parents, node, source) {
                if (parents[node] == -1) {
                    return;
                } else {
                    path.push(parents[node]);
                    this.tracePathRec(path, parents, parents[node], source);
                    return;
                }
            },
            test_graph() {
                addEdge(this.graph, 0, 1, 1);
                addEdge(this.graph, 1, 2, 1);
                addEdge(this.graph, 2, 3, 1);
                addEdge(this.graph, 3, 4, 1);
                addEdge(this.graph, 4, 5, 1);
                addEdge(this.graph, 0, 2, 2);
                addEdge(this.graph, 0, 3, 1);
                addEdge(this.graph, 1, 4, 2);
                let path = dijkstra(this.graph, 0);
                console.log(path);
            },
            show_update(element) {
                console.log(element.currentTarget.id);
                this.show_update_info = true;
                let result = element.currentTarget.id.split("-");
                this.src_update = result[0];
                this.dest_update = result[1];
                //console.log(src + " " + dest);
            },
            update_edge() {
                console.log("update " + this.update_weight);
                let weight = parseInt(this.update_weight);
                updateEdge(this.graph, this.src_update, this.dest_update, weight);
                let id = "" + this.src_update + "-" + this.dest_update;
                let index = this.line_ids.indexOf(id);
                this.$set(this.line_weights, index, this.update_weight);
            },
            remove_edge() {
                console.log("removed");
                removeEdge(this.graph, this.src_update, this.dest_update);
                let id = "" + this.src_update + "-" + this.dest_update;
                let index = this.line_ids.indexOf(id);
                this.$set(this.line_removed, index, true);
            }

        }
    };
</script>

<style>
    .red {
        stroke: rgb(255,0,0);
    }
    .black {
        stroke: rgb(0,0,0);
    }

</style>

