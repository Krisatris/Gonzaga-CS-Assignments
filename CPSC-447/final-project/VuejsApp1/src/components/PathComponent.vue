<template>
    <div class="line">
        <svg height="50" width="50">
            <text fill="#ffffff" font-size="45" font-family="Verdana" :x=line_x :y=line_y>{{weight}}</text>
            <line :x1=this.x1 :y1=this.y1 :x2=x2 :y2=y2 style="stroke:rgb(255,0,0);stroke-width:2" />
        </svg>
    </div>
</template>

<script>
    export default {
        name: 'PathComponent',
        props: {
            weight: String,
            x1: Number,
            x2: Number,
            y1: Number,
            y2: Number,
        },
        computed: {
            line_x() {
                return (this.x1 + this.x2) / 2;
            },
            line_y() {
                return (this.y1 + this.y2) / 2;
            }
        },
        data() {
            return {
                test: ''
            }
        }
    };
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>

