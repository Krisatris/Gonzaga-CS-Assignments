<template>
    <div class="home">
        <h1>{{ msg }}</h1>
        <p>Welcome to your new single-page application, built with <a href="https://vuejs.org" target="_blank">Vue.js</a>.</p>
    </div>
</template>

<script>
    import PathComponent from './PathComponent.vue';
    export default {
        name: 'Home',
        components: {
            PathComponent
        },
        props: {
            msg: String
        }
    };

    
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
</style>

